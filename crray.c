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
    void (*empty)(struct crray * arr);
    int (*count)(struct crray *arr, void *search);
    int (*idx)(struct crray *arr, void *search);
    void *(*find)(struct crray *arr, void *search);
};

int _crray_cmp(void *item, void *search){
    return strcmp(item, search);
}

int crray_resize_if_(struct crray *arr, int size){
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
			memcpy(new, arr->items, arr->esizeof*(arr->length));
			free(arr->items);
		}
		arr->items = new;
		return newsize;
	}
	return arr->allocated;
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
	arr->allocated = crray_resize_if_(arr, arr->esizeof*INITIAL_SIZE);
    arr->cmp = _crray_cmp;
    arr->cmp)(void *item, void *search);
    arr->free)(void *item);
    arr->add_at = crray_add_at_inline
    arr->add = crray_add_inline;
    arr->pop = crray_pop_inline;
    arr->get = crray_get_inline;
    arr->empty crray_empty;
    arr->count = crray_count_inline;
    arr->idx = crray_idx_inline;
    arr->find = crray_idx_inline;
    return arr;
}

int crray_set_inline(struct crray *arr, void *item, int idx){
	if(idx < 0 || idx > arr->length){
		return -1;
	}
    memcpy(arr->items+(arr->esizeof*idx), item, arr->esizeof);
	return 0;
}

int crray_add_at_inline(struct crray *arr, void *item, int idx){
	if(idx == -1){
		return crray_add_at_inline(arr, item, arr->length);
	}
	if(idx < 0 || idx > arr->length){
		return -1;
	}
	arr->allocated = crray_resize_if_(arr, arr->esizeof*(arr->length+1));
    if(idx != arr->length){
        memcpy(arr->items+(arr->esizeof*(arr->length+1)), arr->items+(arr->esizeof*idx), arr->esizeof*(arr->length-idx));
	}
    crray_set_inline(arr, item, idx);
	arr->length++;
	return idx;
}

int crray_add_inline(struct crray *arr, void *item){
  	return crray_add_at_inline(arr, item, -1); 
}

int crray_pop_inline(struct crray *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
		return -1;
	}
    if(result != NULL){
        *result = &arr->items[idx];
    }
	memcpy(arr->items+idx, arr->items+idx+1, arr->esizeof*(arr->length-idx));
	arr->length--;
	return 0;
}

int crray_get_inline(struct crray *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
        return -1;
	}
	*result = arr->items+(arr->esizeof*idx);
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
        if(!arr->cmp(search, &arr->items[i])){
            count++;
        }
    }
    return count;
}

int crray_idx(struct crray *arr, void *search){
    int i;
    for(i=0; i < arr->length; i++){
        if(!arr->cmp(search, &arr->items[i])){
            return i;
        }
    }
    return -1;
}

void *crray_find(struct crray *arr, void *search){
    int i = crray_idx(arr, search);
    if(i != -1){
        return &arr->items[i];
    }
    return NULL;
}
