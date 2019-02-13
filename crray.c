static int INITIAL_SIZE = 4;

typedef int (*crray_cmp)(void *item, void *search);

struct crray {
	int length;
	int allocated;
    crray_cmp cmp;
	void **items;
};

enum CRRAY_STATUS { CRRAY_OK, CRRAY_NOT_FOUND, CRRAY_BOUNDS_ERROR };
typedef int CRRAY_IDX;

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
		new = (void *)malloc(sizeof(void *)*newsize);
		if(!new){
			fprintf(stderr, "oops no memory\n");
			exit(1);
		}
		bzero(new, sizeof(void *)*newsize);
		if(arr->length != 0){
			memcpy(new, arr->items, sizeof(void *)*(arr->length));
			free(arr->items);
		}
		arr->items = new;
		return newsize;
	}
	return arr->allocated;
}

int crray_int_cmp(void *item, void *search){
    return *((int *)item) - *((int *)search);
}

void _crray_init(struct crray *arr, crray_cmp cmp){
	arr->length = 0;
	arr->allocated = 0;
	arr->allocated = crray_resize_if_(arr, INITIAL_SIZE);
    arr->cmp = cmp;
}

struct crray *crray_init(){
	struct crray *arr = (struct crray *)malloc(sizeof(struct crray));
	if(!arr){
		fprintf(stderr, "oops no memory\n");
		exit(1);
	}
	_crray_init(arr, crray_int_cmp);
    return arr;
}

struct crray *crray_init_cmp(crray_cmp cmp){
	struct crray *arr = (struct crray *)malloc(sizeof(struct crray));
	if(!arr){
		fprintf(stderr, "oops no memory\n");
		exit(1);
	}
	_crray_init(arr, cmp);
    return arr;
}


CRRAY_IDX crray_add_at(struct crray *arr, void *item, int idx){
	if(idx == -1){
		return crray_add_at(arr, item, arr->length);
	}
	if(idx < 0 || idx > arr->length){
		return CRRAY_BOUNDS_ERROR;
	}
	arr->allocated = crray_resize_if_(arr, arr->length+1);
        if(idx != arr->length){
		memcpy(arr->items+idx+1, arr->items+idx, sizeof(void *)*(arr->length-idx));
	}
	arr->items[idx] = item;
	arr->length++;
	return idx;
}


CRRAY_IDX crray_add(struct crray *arr, void *item){
  	return crray_add_at(arr, item, -1); 
}

enum CRRAY_STATUS crray_set(struct crray *arr, void *item, int idx){
	if(idx < 0 || idx > arr->length-1){
		return CRRAY_BOUNDS_ERROR;
	}
	arr->items[idx] = item;
	return CRRAY_OK;
}

enum CRRAY_STATUS crray_get(struct crray *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
		return CRRAY_BOUNDS_ERROR;
	}
	*result = arr->items[idx];
	return CRRAY_OK;
}

enum CRRAY_STATUS crray_pop(struct crray *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
		return CRRAY_BOUNDS_ERROR;
	}
    if(result != NULL){
        *result = arr->items[idx];
    }
	memcpy(arr->items+idx, arr->items+idx+1, sizeof(void *)*(arr->length-idx));
	arr->length--;
	return CRRAY_OK;
}

enum CRRAY_STATUS crray_pop_many(struct crray *arr, int idx, int size, struct crray **result){
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
	return CRRAY_OK;
}

void crray_free(struct crray *arr){
    int i;
    for(i=0; i < arr->length; i++){
        free(arr->items[i]);
    }
    free(arr);
}

void crray_empty(struct crray * arr, int should_free){
    if(should_free){
        int i;
        for(i=0; i < arr->length; i++){
            free(arr->items[i]);
        }
    }
    arr->length = 0;
}

int crray_count(struct crray *arr, void *search){
    int i;
    int count = 0;
    for(i=0; i < arr->length; i++){
        if(!arr->cmp(search, arr->items[i])){
            count++;
        }
    }
    return count;
}

int crray_idx(struct crray *arr, void *search){
    int i;
    for(i=0; i < arr->length; i++){
        if(!arr->cmp(search, arr->items[i])){
            return i;
        }
    }
    return -1;
}

void *crray_find(struct crray *arr, void *search){
    int i = crray_idx(arr, search);
    if(i != -1){
        return arr->items[i];
    }
    return NULL;
}
