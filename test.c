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
	printf("charlie alloc:%d length:%d\n", arr->allocated, arr->length);

	char *aback1;
	get(arr, 0, &aback1);
	printf("result from 0 :%s\n", aback1);

	char *aback2;
	get(arr, 1, &aback2);
	printf("result from 1 :%s\n", aback2);

	char *aback3;
	get(arr, 2, &aback3);
	printf("result from 1 :%s\n", aback3);


	char delta[] = "delta";
	add(arr, &delta);
	printf("delta alloc:%d length:%d\n", arr->allocated, arr->length);

	char echo[] = "echo";
	add(arr, &echo);
	printf("echo alloc:%d length:%d\n", arr->allocated, arr->length);

	char foxtrot[] = "foxtrot";
	add(arr, &foxtrot);
	printf("foxtrot alloc:%d length:%d\n", arr->allocated, arr->length);

	char golf[] = "golf";
	add(arr, &golf);
	printf("golf alloc:%d length:%d\n", arr->allocated, arr->length);

	char hotel[] = "hotel";
	add(arr, &hotel);
	printf("hotel alloc:%d length:%d\n", arr->allocated, arr->length);

	char india[] = "india";
	add(arr, &india);
	printf("india alloc:%d length:%d\n", arr->allocated, arr->length);

	char juliet[] = "juliet";
	add(arr, &juliet);
	printf("juliet alloc:%d length:%d\n", arr->allocated, arr->length);


	char override[] = "override";	
	set(arr, &override, 3);

	char *bback1;
	get(arr, 3, &bback1);
	printf("result from set 3 :%s\n", bback1);

}


