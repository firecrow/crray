#include <stdlib.h>
#include <stdio.h>
#include "crray.inc.h"
#include "crray.c"

void show_arr(struct crray *arr, char *label){
	printf(">'%s' alloc:%d length:%d\n", label, arr->allocated, arr->length);
	int i;
	void *value;
	for(i=0; i<arr->length; i++){
		crray_get(arr, i, &value);
		printf("%d= %s\n", i, (char *)value);
	}
}


int main(int argc, char **argv){

/*
	struct crray *arr = crray_init();
	printf("alloc:%d length:%d\n", arr->allocated, arr->length);

	char alpha[] = "alpha";
	char bravo[] = "bravo";

	int a = crray_add(arr, &alpha);
	printf("a:%d\n", a);
	int b = crray_add(arr, &bravo);
	printf("b:%d\n", b);
	printf("alloc:%d length:%d\n", arr->allocated, arr->length);
	show_arr(arr, "two adds");

	char charlie[] = "charlie"; 
	int c = crray_add_at(arr, &charlie, 1);
	show_arr(arr, "add charlie at idx 1");

	char delta[] = "delta";
	crray_add(arr, &delta);
	show_arr(arr, "+1");

	char echo[] = "echo";
	crray_add(arr, &echo);
	show_arr(arr, "+1");

	char foxtrot[] = "foxtrot";
	crray_add(arr, &foxtrot);
	show_arr(arr, "+1");

	char golf[] = "golf";
	crray_add(arr, &golf);
	show_arr(arr, "+1");

	char hotel[] = "hotel";
	crray_add(arr, &hotel);
	show_arr(arr, "+1");

	char india[] = "india";
	crray_add(arr, &india);
	show_arr(arr, "+1");

	char juliet[] = "juliet";
	crray_add(arr, &juliet);
	show_arr(arr, "+1");

	char override[] = "override";	
	crray_set(arr, &override, 3);

	show_arr(arr, "set at idx 3");
	void *out;
	crray_pop(arr, 2, &out);
	printf("out:%s\n", (char *)out);
	show_arr(arr, "pop at idx 2");

	show_arr(arr, "set at idx 3");
	crray_pop(arr, 5, &out);
	printf("out:%s\n", (char *)out);
	show_arr(arr, "pop at idx 5");

	struct crray *presult;
	crray_pop_many(arr, 2, 3, &presult);
	show_arr(presult, "poped");
	show_arr(arr, "pop many 3 from idx 2");
*/
}

