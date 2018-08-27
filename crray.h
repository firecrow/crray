

static INITIAL_SIZE = 4;


struct crray {
	int length;
	int allocated;
	void **items;
};

enum CRRAY_STATUS { CRRAY_OK, CRRAY_NOT_FOUND };
typedef int CRRAY_IDX;

int resize_if_(struct crray *arr, int size){
	int newsize;
	if(arr->allocated > 0) {
		newsize = arr->allocated;
		while((newsize = newsize*2*2) < size){}
	}else{
		newsize = size;	
	}
	void *new = NULL;
	if(arr->allocated < size){
		new = (void *)malloc(sizeof(void *)*newsize);
		if(!new){
			printf("oops no memory");
			exit(1);
		}
	}
	if(arr->length != 0){
		memcpy(new, arr->items, sizeof(void *)*arr->length);
		free(arr->items);
	}
	arr->items = new;
	return newsize;
}

struct crray *crray_init(){
	struct crray *arr = (struct crray *)malloc(sizeof(struct crray));
	if(!arr){
		printf("oops no memory");
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
   
}

enum CRRAY_STATUS get(struct crray *arr, void *item, int idx, void **result){
   
}

enum CRRAY_STATUS pop(struct crray *arr, void *item, int idx, void **result){
   
}

enum CRRAY_STATUS pop_many(struct crray *arr, void *item, int idx, int size, struct crray **result){
   
}
