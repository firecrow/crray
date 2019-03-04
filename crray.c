static int INITIAL_SIZE = 4;

struct crray {
	int length;
	int allocated;
    size_t esizeof;
	char *items;
    int (*cmp)(void *item, void *search);
    int (*free)(void *item);
    int (*add_at)(struct crray *arr, void *item, int idx);
    int (*add)(struct crray *arr, void *item);
    int (*pop)(struct crray *arr, int idx, void **result);
    int (*get)(struct crray *arr, int idx, void **result);
    int (*set)(struct crray *arr, void *item, int idx);
    void (*empty)(struct crray * arr);
    int (*count)(struct crray *arr, void *search);
    int (*idx)(struct crray *arr, void *search);
    int (*find)(struct crray *arr, void *search, void **result);
};

int _crray_resize_if(struct crray *arr, int size){
	int newsize;
	char *new = NULL;
	if(arr->allocated < size){
		if(arr->allocated > 0) {
			newsize = arr->allocated;
			while((newsize = newsize*2*2) < size){}
		}else{
			newsize = size;
		}
		new = (void *)malloc(arr->esizeof*newsize);
        bzero(new, arr->esizeof*newsize);
		if(!new){
			fprintf(stderr, "oops no memory\n");
			exit(1);
		}
		if(arr->length != 0){
			memmove(new, arr->items, arr->esizeof*(arr->length));
			free(arr->items);
		}
		arr->items = new;
		return newsize;
	}
	return arr->allocated;
}

size_t esize(struct crray *arr, int q){
    return arr->esizeof*q;
}

void *eptr(struct crray *arr, int idx){
    return arr->items+esize(arr, idx);
}

int crray_set(struct crray *arr, void *item, int idx){
	if(idx < 0 || idx > arr->length){
		return -1;
	}
    memmove(eptr(arr, idx), item, arr->esizeof);
	return 0;
}

int crray_add_at(struct crray *arr, void *item, int idx){
	if(idx == -1){
		return crray_add_at(arr, item, arr->length);
	}
	if(idx < 0 || idx > arr->length){
		return -1;
	}
	arr->allocated = _crray_resize_if(arr, esize(arr, arr->length+1));
    if(idx != arr->length){
        memmove(eptr(arr, idx+1), eptr(arr, idx), esize(arr, arr->length-idx));
	}
    crray_set(arr, item, idx);
	arr->length++;
	return idx;
}

int crray_add(struct crray *arr, void *item){
  	return crray_add_at(arr, item, -1); 
}

int crray_pop(struct crray *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
		return -1;
	}
    void *r = malloc(arr->esizeof);
    memcpy(r, eptr(arr, idx), arr->esizeof);
	*result = r;
	memmove(eptr(arr, idx), eptr(arr, idx+1), esize(arr, arr->length-idx));
	arr->length--;
	return 0;
}

int crray_get(struct crray *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
        return -1;
	}
	*result = eptr(arr, idx);
	return 0;
}

void crray_empty(struct crray * arr){
    if(arr->free){
        int i;
        for(i=0; i < arr->length; i++){
            arr->free(&arr->items[i]);
        }
    }
    arr->length = 0;
}

int crray_count(struct crray *arr, void *search){
    int i;
    int count = 0;
    for(i=0; i < arr->length; i++){
        if(!arr->cmp(search, eptr(arr, i))){
            count++;
        }
    }
    return count;
}

int crray_idx(struct crray *arr, void *search){
    int i;
    for(i=0; i < arr->length; i++){
        if(!arr->cmp(search, eptr(arr, i))){
            return i;
        }
    }
    return -1;
}

int crray_find(struct crray *arr, void *search, void **result){
    int i = crray_idx(arr, search);
    if(i != -1){
        *result = arr->items+(arr->esizeof*i);
        return i;
    }
    *result = NULL;
    return -1;
}

int _crray_cmp(void *item, void *search){
    return 0;
}

int _crray_str_cmp(void *item, void *search){
    return strncmp(item, search, 1024);
}

int _crray_int_cmp(void *item, void *search){
    return *(int *)item - *(int *)search;
}

struct crray *crray_init(size_t esizeof){
    struct crray *arr = malloc(sizeof(struct crray));
    if(!arr){
        fprintf(stderr, "no memory for crray_init");
    }
    bzero(arr, sizeof(struct crray));
	arr->length = 0;
    arr->esizeof = esizeof;
	arr->allocated = 0;
	arr->allocated = _crray_resize_if(arr, arr->esizeof*INITIAL_SIZE);
    arr->cmp = _crray_cmp;
    arr->free = NULL;
    arr->add_at = crray_add_at;
    arr->add = crray_add;
    arr->pop = crray_pop;
    arr->get = crray_get;
    arr->set = crray_set;
    arr->empty = crray_empty;
    arr->count = crray_count;
    arr->idx = crray_idx;
    arr->find = crray_find;
    return arr;
}

struct crray *crray_ptr_init(){
    struct crray *arr = crray_init(sizeof(void *));
    return arr;
}

struct crray *crray_str_init(){
    struct crray *arr = crray_init(sizeof(void *));
    arr->cmp = _crray_str_cmp;
    return arr;
}

struct crray *crray_int_init(){
    struct crray *arr = crray_init(sizeof(int));
    arr->cmp = _crray_int_cmp;
    return arr;
}
