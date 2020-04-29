#define CLASSES_PTRARRAY 13
#define BLOCK_SIZE 4 

struct ptrarray {
    struct base base;
    void **content;
    size_t length;
    size_t alloc_length;
};

void ptrarray_free(void *_arr){
    struct ptrarray *arr = (struct ptrarray *)_arr;
    int i; 
    for(i=0; i< arr->length; i++){
        ref_decr(arr->content[i]);
    }
    free(arr);
}

struct ptrarray *ptrarray_alloc(size_t initial_size){
    struct ptrarray *arr;
    xokptr(arr = malloc(sizeof(struct ptrarray)));
    bzero(arr, sizeof(struct ptrarray));
    if(initial_size < BLOCK_SIZE) initial_size = BLOCK_SIZE;
    xokptr(arr->content = malloc(initial_size*sizeof(void *)));
    arr->alloc_length = initial_size;
    arr->base.class = CLASSES_PTRARRAY;
    arr->base.free = ptrarray_free;
    return arr;
}

void arr_push(struct ptrarray *arr, struct abstract *obj, int idx){
    if(arr->length+1 > arr->alloc_length){
        arr->alloc_length = arr->alloc_length*2;
        xokptr(arr->content = realloc(arr->content, arr->alloc_length*sizeof(void *)));
    }
    if(idx == -1) idx = arr->length;
    else memmove(arr->content[idx+1], arr->content[idx], arr->length-idx);
    /*arr->content[idx] = ref_incr(obj);*/
    arr->content[idx] = obj;
    arr->length++;
}

void arr_pop(struct ptrarray *arr, struct abstract *obj, int idx){
    memmove(arr->content[idx], arr->content[idx+1], arr->length-idx);
    arr->length--;
}
