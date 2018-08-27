

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
	if(idx < 0 || idx > arr->length-1){
		return CRRAY_BOUNDS_ERROR;
	}
	arr->items[idx] = item;
	return CRRAY_OK;
}

CRRAY_IDX add_at(struct crray *arr, void *item, int idx){
	if(idx == -1){
		return add_at(arr, item, arr->length);
	}
	if(idx < 0 || idx > arr->length){
		return CRRAY_BOUNDS_ERROR;
	}
	arr->allocated = resize_if_(arr, arr->length+1);
        if(idx != arr->length){
		memcpy(arr->items+idx+1, arr->items+idx, sizeof(void *)*(arr->length-idx));
	}
	arr->items[idx] = item;
	arr->length++;
	return idx;
}

enum CRRAY_STATUS get(struct crray *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
		return CRRAY_BOUNDS_ERROR;
	}
	*result = arr->items[idx];
	return CRRAY_OK;
}

enum CRRAY_STATUS pop(struct crray *arr, int idx, void **result){
	if(idx < 0 || idx > arr->length-1){
		return CRRAY_BOUNDS_ERROR;
	}
	*result = arr->items[idx];
	memcpy(arr->items+idx, arr->items+idx+1, sizeof(void *)*(arr->length-idx));
	arr->length--;
	return CRRAY_OK;
}

enum CRRAY_STATUS pop_many(struct crray *arr, int idx, int size, struct crray **result){
	if(idx < 0 || idx > arr->length-1-size){
		return CRRAY_BOUNDS_ERROR;
	}
	struct crray *out = crray_init();
	arr->allocated = resize_if_(arr, size);
	memcpy(out->items, arr->items+idx, sizeof(void *)*size);
	out->length = size;
	*result = out;
	memcpy(arr->items+idx, arr->items+idx+size, sizeof(void *)*(arr->length-idx));
	arr->length -= size;
	return CRRAY_OK;
}
