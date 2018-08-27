#include <stdio.h>
#include "crray.h"

int main(int argc, char **argv){
	printf("hi\n");

	struct crray *arr = crray_init();
	printf("alloc:%d length:%d\n", arr->allocated, arr->length);

	char alpha[] = "alpha";
	char bravo[] = "bravo";

	int a = add(arr, &alpha);
	printf("a:%d\n", a);
	int b = add(arr, &bravo);
	printf("b:%d\n", b);
	printf("alloc:%d length:%d\n", arr->allocated, arr->length);

	char *hiback;
	get(arr, 0, &hiback);
	printf("result from 0 :%s\n", hiback);

	char *pooback;
	get(arr, 1, &pooback);
	printf("result from 1 :%s\n", pooback);


	char charlie[] = "charlie"; 
	int c = add_at(arr, &charlie, 1);
	printf("alloc:%d length:%d\n", arr->allocated, arr->length);

	char *aback1;
	get(arr, 0, &aback1);
	printf("result from 0 :%s\n", aback1);

	char *aback2;
	get(arr, 1, &aback2);
	printf("result from 1 :%s\n", aback2);

	char *aback3;
	get(arr, 2, &aback3);
	printf("result from 1 :%s\n", aback3);

}


