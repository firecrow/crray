static int INITIAL_SIZE = 4;

struct crray {
	int length;
	int allocated;
    size_t sizeof;
	void **items;
};

typedef int (*crray_cmp)(void *item, void *search);
typedef int (*crray_free)(void *item);
struct crray_ptr {
	int length;
	int allocated;
    size_t sizeof;
	void **items;
    crray_cmp cmp;
    crray_free free;
};

typedef int (*crray_int_cmp)(int item, int search);
typedef int (*crray_int_free)(int item);
struct crray_int {
	int length;
	int allocated;
    size_t sizeof;
	void **items;
    crray_int_cmp cmp;
    crray_int_free free;
};

/* ----------------------- generic ---------------------- */
int crray_resize_if_(struct crray *arr, int size){
	int newsize;
	void *new = NULL;
	if(arr->allocated < size){
		if(arr->allocated > 0) {
			newsize = arr->allocated;
			while((newsize = newsize*2*2) < size){}
		}else{
			newsize = size;
		}
		new = (void *)malloc(arr->sizeof*newsize);
		if(!new){
			fprintf(stderr, "oops no memory\n");
			exit(1);
		}
		bzero(new, sizeof(void *)*newsize);
		if(arr->length != 0){
			memcpy(new, arr->items, arr->sizeof*(arr->length));
			free(arr->items);
		}
		arr->items = new;
		return newsize;
	}
	return arr->allocated;
}


void _crray_init(struct crray *arr, size_t sizeof){
	arr->length = 0;
    arr->sizeof = sizeof;
	arr->allocated = 0;
	arr->allocated = crray_resize_if_(arr, INITIAL_SIZE);
}

int crray_add_at(struct crray *arr, void item, int idx){
	if(idx == -1){
		return crray_add_at(arr, item, arr->length);
	}
	if(idx < 0 || idx > arr->length){
		return -1;
	}
	arr->allocated = crray_resize_if_(arr, arr->length+1);
        if(idx != arr->length){
		memcpy(arr->items+idx+1, arr->items+idx, arr->sizeof*(arr->length-idx));
	}
    memcpy(arr->items+idx, item, arr->sizeof*(arr->length-idx));
	arr->length++;
	return idx;
}


int crray_add(struct crray *arr, void item){
  	return crray_add_at(arr, item, -1); 
}

int crray_set(struct crray *arr, void item, int idx){
	if(idx < 0 || idx > arr->length-1){
		return -1;
	}
    crray_add_at(arr, item, idx);
	return 0;
}

enum crray_status crray_pop(struct crray *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
		return CRRAY_BOUNDS_ERROR;
	}
    if(result != NULL){
        *result = arr->items[idx];
    }
	memcpy(arr->items+idx, arr->items+idx+1, arr->sizeof*(arr->length-idx));
	arr->length--;
	return 0;
}

enum crray_status crray_pop_many(struct crray *arr, int idx, int size, struct crray **result){
	if(idx < 0 || idx > arr->length-1-size){
		return CRRAY_BOUNDS_ERROR;
	}
	struct crray *out = crray_init();
	arr->allocated = crray_resize_if_(arr, size);
	memcpy(out->items, arr->items+idx, sizeof(void *)*size);
	out->length = size;
	*result = out;
	memcpy(arr->items+idx, arr->items+idx+size, sizeof(void *)*(arr->length-idx));
	arr->length -= size;
	return 0;
}

/* ----------------------- specific ---------------------- */

int crray_int_cmp(void int, void int){
    return item - search;
}

int crray_cmp(void *item, void *search){
    return strcmp(item, search);
}

int crray_get(struct crray_ptr *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
        return -1;
	}
	*result = arr->items[idx];
	return 0;
}

int crray_int_get(struct crray_int *arr, int idx, int *result){
	if(idx < 0 || idx > arr->length-1){
        return -1;
	}
	*result = arr->items[idx];
	return 0;
}

void crray_empty(struct crray_ptr * arr, int should_free){
    if(should_free){
        int i;
        for(i=0; i < arr->length; i++){
            arr->free(arr->items[i]);
        }
    }
    arr->length = 0;
}

void crray_int_empty(struct crray_int * arr){
    arr->length = 0;
}

int crray_count(struct crray_ptr *arr, void *search){
    int i;
    int count = 0;
    for(i=0; i < arr->length; i++){
        if(!arr->cmp(search, arr->items[i])){
            count++;
        }
    }
    return count;
}

int crray_int_count(struct crray_int *arr, int search){
    int i;
    int count = 0;
    for(i=0; i < arr->length; i++){
        if(!arr->cmp(search, arr->items[i])){
            count++;
        }
    }
    return count;
}

int crray_idx(struct crray_ptr *arr, void *search){
    int i;
    for(i=0; i < arr->length; i++){
        if(!arr->cmp(search, arr->items[i])){
            return i;
        }
    }
    return -1;
}

int crray_int_idx(struct crray_int *arr, int search){
    int i;
    for(i=0; i < arr->length; i++){
        if(!arr->cmp(search, arr->items[i])){
            return i;
        }
    }
    return -1;
}

void *crray_find(struct crray_ptr *arr, void *search){
    int i = crray_idx(arr, search);
    if(i != -1){
        return &arr->items[i];
    }
    return NULL;
}

void *crray_int_find(struct crray_int *arr, int search){
    int i = crray_int_idx(arr, search);
    if(i != -1){
        return &arr->items[i];
    }
    return NULL;
}
