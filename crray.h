

static INITIAL_SIZE = 4;


struct crray {
	int length;
	int allocated;
	void **items;
};

enum CRRAY_STATUS { CRRAY_OK, CRRAY_NOT_FOUND, CRRAY_BOUNDS_ERROR };
typedef int CRRAY_IDX;

int resize_if_(struct crray *arr, int size){
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
			printf("oops no memory\n");
			exit(1);
		}
		if(arr->length != 0){
			memcpy(new, arr->items, sizeof(void *)*(arr->length-1));
			free(arr->items);
		}
		arr->items = new;
		return newsize;
	}
	return arr->allocated;
}

struct crray *crray_init(){
	struct crray *arr = (struct crray *)malloc(sizeof(struct crray));
	if(!arr){
		printf("oops no memory\n");
		exit(1);
	}
	arr->length = 0;
	arr->allocated = 0;
	arr->allocated = resize_if_(arr, INITIAL_SIZE);
	return arr;
}

CRRAY_IDX add(struct crray *arr, void *item){
  	return add_at(arr, item, -1); 
}

enum CRRAY_STATUS set(struct crray *arr, void *item, int idx){
}

CRRAY_IDX add_at(struct crray *arr, void *item, int idx){
	printf("hi 1\n");
	if(idx == -1){
		return add_at(arr, item, arr->length);
	}
	printf("hi 2\n");
	if(idx > arr->length){
		return CRRAY_BOUNDS_ERROR;
	}
	printf("hi 3\n");
	arr->allocated = resize_if_(arr, arr->length+1);
        if(idx != arr->length){
		printf("hi 4 not supposed to be here\n");
		memcpy(arr->items+idx, arr->items+(idx-1), sizeof(void *)*(arr->length-idx+1));
	}
	arr->items[idx] = item;
	arr->length++;
	printf("hi 5\n");
	return idx;
}

enum CRRAY_STATUS get(struct crray *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
		return CRRAY_BOUNDS_ERROR;
	}
	*result = arr->items[idx];
	return CRRAY_OK;
}

enum CRRAY_STATUS pop(struct crray *arr, void *item, int idx, void **result){
   
}

enum CRRAY_STATUS pop_many(struct crray *arr, void *item, int idx, int size, struct crray **result){
   
}
