/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */
#define BLOCK_SIZE 4 

typedef struct crrray {
    struct base base;
    enum classes generic;
    void **content;
    size_t length;
    size_t alloc_length;
} Crray;

static void ctl_crray_free(void *_arr){
    Crray *arr = (Crray *)_arr;
    int i; 
    for(i=0; i< arr->length; i++){
        ctl_ref_decr(arr->content[i]);
    }
    free(arr);
}

Crray *ctl_crray_incr(Crray *crray){
    return (Crray *)ctl_ref_incr((CtlAbs *)crray);
}

Crray *ctl_crray_decr(Crray *crray){
    return (Crray *)ctl_ref_decr((CtlAbs *)crray);
}

Crray *ctl_crray_alloc(size_t initial_size){
    Crray *arr;
    ctl_xptr(arr = malloc(sizeof(Crray)));
    bzero(arr, sizeof(Crray));
    if(initial_size < BLOCK_SIZE) initial_size = BLOCK_SIZE;
    ctl_xptr(arr->content = malloc(initial_size*sizeof(void *)));
    arr->alloc_length = initial_size;
    arr->base.class = CLASS_PTRARRAY;
    arr->base.free = ctl_crray_free;
    return arr;
}

void ctl_crray_push(Crray *arr, CtlAbs *obj, int idx){
    if(arr->length+1 > arr->alloc_length){
        arr->alloc_length = arr->alloc_length*2;
        ctl_xptr(arr->content = realloc(arr->content, arr->alloc_length*sizeof(void *)));
    }
    if(idx == -1) idx = arr->length;
    else memmove(arr->content+(idx+1), arr->content+idx, (arr->length-idx)*sizeof(void*));
    arr->content[idx] = ctl_ref_incr(obj);
    arr->length++;
}

void ctl_crray_remove(Crray *arr, int idx){
    ctl_ref_decr(arr->content[idx]);
    memmove(arr->content+idx, arr->content+(idx+1), (arr->length-idx)*sizeof(void *));
    arr->length--;
}

Crray *ctl_split(CtlCounted *str, CtlCounted *sep){
    char *p  = str->data;
    char *b  = p;
    char *s = sep->data;
    Crray *arr = ctl_crray_alloc(0);
    while(p-str->data < str->length){
        if(*p++ == *s){ s++;
        } else s = sep->data;
        if(s-sep->data == sep->length){
            ctl_crray_push(arr, (CtlAbs *)ctl_counted_alloc(b, p-b-sep->length), -1);
            b = p;
            s = sep->data;
        }
    }
    if(b != p){
        ctl_crray_push(arr, (CtlAbs *)ctl_counted_alloc(b, p-b), -1);
    }
    return arr;
}

CtlCounted *ctl_join(Crray *arr, CtlCounted *sep){
    CtlCounted *c = clone((CtlCounted *)arr->content[0]);
    CtlCounted *y;
    for(int i = 1; i< arr->length; i++) { 
        y = (CtlCounted *)arr->content[i];
        ctl_counted_push(c, sep->data, sep->length);
        ctl_counted_push(c, y->data, y->length);
    }
    return c;
}

void ctl_crray_sort(Crray *arr, int (*cmp)(CtlAbs *a, CtlAbs *b) ){
    ;
}

Crray *ctl_crray_filter(Crray *arr, int (*cmp)(CtlAbs *a, CtlAbs *b) ){
    ;
}

CtlAbs *ctl_crray_find(Crray *arr, CtlAbs *needle, int (*cmp)(CtlAbs *a, CtlAbs *b) ){
    ;
}
