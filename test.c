#include <stdio.h>
#include "crray.h"

void show_arr(struct crray *arr, char *label){
	printf(">'%s' alloc:%d length:%d\n", label, arr->allocated, arr->length);
	int i;
	char *value;
	for(i=0; i<arr->length; i++){
		get(arr, i, &value);
		printf("%d= %s\n", i, value);
	}
}


int main(int argc, char **argv){

	struct crray *arr = crray_init();
	printf("alloc:%d length:%d\n", arr->allocated, arr->length);

	char alpha[] = "alpha";
	char bravo[] = "bravo";

	int a = add(arr, &alpha);
	printf("a:%d\n", a);
	int b = add(arr, &bravo);
	printf("b:%d\n", b);
	printf("alloc:%d length:%d\n", arr->allocated, arr->length);
	show_arr(arr, "two adds");

	char charlie[] = "charlie"; 
	int c = add_at(arr, &charlie, 1);
	show_arr(arr, "add charlie at idx 1");

	char delta[] = "delta";
	add(arr, &delta);
	show_arr(arr, "+1");

	char echo[] = "echo";
	add(arr, &echo);
	show_arr(arr, "+1");

	char foxtrot[] = "foxtrot";
	add(arr, &foxtrot);
	show_arr(arr, "+1");

	char golf[] = "golf";
	add(arr, &golf);
	show_arr(arr, "+1");

	char hotel[] = "hotel";
	add(arr, &hotel);
	show_arr(arr, "+1");

	char india[] = "india";
	add(arr, &india);
	show_arr(arr, "+1");

	char juliet[] = "juliet";
	add(arr, &juliet);
	show_arr(arr, "+1");

	char override[] = "override";	
	set(arr, &override, 3);

	show_arr(arr, "set at idx 3");
	char *out;
	pop(arr, 2, &out);
	printf("out:%s\n", out);
	show_arr(arr, "pop at idx 2");

	show_arr(arr, "set at idx 3");
	pop(arr, 5, &out);
	printf("out:%s\n", out);
	show_arr(arr, "pop at idx 5");

	struct crray *presult;
	pop_many(arr, 2, 3, &presult);
	show_arr(presult, "poped");
	show_arr(arr, "pop many 3 from idx 2");
}


