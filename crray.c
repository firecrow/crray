#define BLOCK_SIZE 4 

typedef struct crrray {
    struct base base;
    enum classes generic;
    void **content;
    size_t length;
    size_t alloc_length;
} Crray;

void crray_free(void *_arr){
    Crray *arr = (Crray *)_arr;
    int i; 
    for(i=0; i< arr->length; i++){
        ref_decr(arr->content[i]);
    }
    free(arr);
}

Crray *crray_alloc(size_t initial_size){
    Crray *arr;
    xokptr(arr = malloc(sizeof(Crray)));
    bzero(arr, sizeof(Crray));
    if(initial_size < BLOCK_SIZE) initial_size = BLOCK_SIZE;
    xokptr(arr->content = malloc(initial_size*sizeof(void *)));
    arr->alloc_length = initial_size;
    arr->base.class = CLASS_PTRARRAY;
    arr->base.free = crray_free;
    return arr;
}

void crray_push(Crray *arr, struct abstract *obj, int idx){
    if(arr->length+1 > arr->alloc_length){
        arr->alloc_length = arr->alloc_length*2;
        xokptr(arr->content = realloc(arr->content, arr->alloc_length*sizeof(void *)));
    }
    if(idx == -1) idx = arr->length;
    else memmove(arr->content+(idx+1), arr->content+idx, (arr->length-idx)*sizeof(void*));
    /*arr->content[idx] = ref_incr(obj);*/
    arr->content[idx] = obj;
    arr->length++;
}

void crray_remove(Crray *arr, int idx){
    ref_decr(arr->content[idx]);
    memmove(arr->content+idx, arr->content+(idx+1), (arr->length-idx)*sizeof(void *));
    arr->length--;
}

Crray *split(Counted *str, Counted *sep){
    char *p  = str->data;
    char *b  = p;
    char *s = sep->data;
    Crray *arr = crray_alloc(0);
    while(p-str->data < str->length){
        if(*p++ == *s){ s++;
        } else s = sep->data;
        if(s-sep->data == sep->length){
            crray_push(arr, (struct abstract *)counted_alloc(b, p-b-sep->length), -1);
            b = p;
            s = sep->data;
        }
    }
    if(b != p){
        crray_push(arr, (struct abstract *)counted_alloc(b, p-b), -1);
    }
    return arr;
}

Counted *join(Crray *arr, Counted *sep){
    Counted *c = clone((Counted *)arr->content[0]);
    Counted *y;
    for(int i = 1; i< arr->length; i++) { 
        y = (Counted *)arr->content[i];
        counted_push(c, sep->data, sep->length);
        counted_push(c, y->data, y->length);
    }
    return c;
}
