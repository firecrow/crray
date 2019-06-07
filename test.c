#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "crray.inc.h"
#include "crray.c"

void show_int_arr(struct crray *arr, char *label){
    printf("--- %s ---\n", label);
	int i;
	void *value;
	for(i=0; i<arr->length; i++){
		arr->get(arr, i, &value);
		printf("%d=%d\n", i, *(int *)value);
	}
}

void show_str_arr(struct crray *arr, char *label){
  printf("--- %s ---\n", label);
	int i;
	void *value;
	for(i=0; i<arr->length; i++){
		arr->get(arr, i, &value);
		printf("%d=%s\n", i, (char *)value);
	}
}

int compare_arr(struct crray *a, struct crray *b){
    int i;
    for(i=0; i < a->length; i++){
        if(a->cmp(a->items+(a->esizeof*i), b->items+(b->esizeof*i))){
            return -1;
        }
    }
    return 0;
}

void int_tests(){

	struct crray *arr = crray_int_init();

    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int five = 5;
    int thirty = 30;
    int idx;
    int *r1;
    int *r2;
    int *r3;
    int *r4;
    int *r5;
    int *rpop;

    arr->add(arr, &one);
    arr->add(arr, &two);

    arr->get(arr, 0, (void *)&r1);
    arr->get(arr, 1, (void *)&r2);

    /* show_int_arr(arr, "add/get 2"); */
    (*r1 == 1) ? printf("pass") : printf("fail");
    printf(" 1 == 1 set/get\n");

    (*r2 == 2) ? printf("pass") : printf("fail");
    printf(" 2 == 2 set/get\n");

    int *first = (int *)arr->items;
    int *second = ((int *)arr->items)+(arr->length-1);
    (*first == 1) ? printf("pass") : printf("fail");
    printf(" 1 == 1 items\n");

    (*second == 2) ? printf("pass") : printf("fail");
    printf(" 2 == 2 items\n");

    arr->add(arr, &four);
    arr->add(arr, &five);
    arr->get(arr, 0, (void *)&r1);
    arr->get(arr, 1, (void *)&r2);
    arr->get(arr, 2, (void *)&r3);
    arr->get(arr, 3, (void *)&r4);
    arr->get(arr, 4, (void *)&r5);

    /*show_int_arr(arr, "add/get 5");*/
    (*r1 == 1 && *r2 == 2 && *r3 == 4 && *r4 == 5) ? printf("pass") : printf("fail");
    printf(" four items set/get\n");

    arr->add_at(arr, &three, 2);
    arr->get(arr, 0, (void *)&r1);
    arr->get(arr, 1, (void *)&r2);
    arr->get(arr, 2, (void *)&r3);
    arr->get(arr, 3, (void *)&r4);
    arr->get(arr, 4, (void *)&r5);
    /*show_int_arr(arr, "add_at");*/
    (*r1 == 1 && *r2 == 2 && *r3 == 3 && *r4 == 4 && *r5 == 5) ? printf("pass") : printf("fail");
    printf(" five items add_at\n");

    /*
    idx = arr->idx(arr, &two);
    (idx == 1) ? printf("pass") : printf("fail");
    printf(" idx of two is 1 == %d\n", idx);
    */


    arr->set(arr, (void *)&thirty, 2);
    /*show_int_arr(arr, "set");*/
    arr->get(arr, 2, (void *)&r3);
    (*r3 == 30) ? printf("pass") : printf("fail");
    printf(" set idx 30 == %d\n", *r3);

    /*
    int *rfind;
    idx = arr->find(arr, &two, (void *)&rfind);
    (*rfind == 2 && idx == 1) ? printf("pass") : printf("fail");
    printf(" find idx 1 == %d and value  2 == %d\n", idx, *rfind);
    */

    struct crray *a = crray_int_init();
    struct crray *b = crray_int_init();
    a->add(a, &one);
    a->add(a, &two);
    a->add(a, &three);
    a->add(a, &four);
    /*show_int_arr(a, "a");*/

    b->add(b, &one);
    b->add(b, &two);
    b->add(b, &four);
    /*show_int_arr(b, "b");*/

    int *vpop;
    a->pop(a, 2, (void *)&vpop);
    /*show_int_arr(a, "after pop");*/
    int spop = compare_arr(a, b); 
    (*vpop == 3 && spop == 0) ? printf("pass") : printf("fail");
    printf(" pop idx 2 equiv? %d 3 == %d \n", spop, *vpop);

    a = crray_int_init();
    a->add(a, &one);
    a->add(a, &one);
    a->add(a, &one);
    a->add(a, &two);
    a->add(a, &three);
    a->add(a, &three);
    a->add(a, &four);
    int count_one = a->count(a, &one);
    int count_two = a->count(a, &two);
    int count_three = a->count(a, &three); 
    int count_thirty = a->count(a, &thirty); 
    (count_one == 3 && count_two == 1 && count_three == 2 & count_thirty == 0) ? printf("pass") : printf("fail");
    printf(" count tests one 3 == %d two 1 == %d three 2 == %d thirty 0 == %d \n", count_one, count_two, count_three, count_thirty);

}

void ptr_tests(){
    char *back;
    char *one = "one";
    char *two = "two";
    char *three = "three";
    char *four = "four";
    char *five = "five";

  	struct crray *arr = crray_str_init();
    arr->add(arr, one);
    arr->add(arr, two);
    arr->add(arr, three);
    arr->add(arr, four);
    arr->get(arr, 2, (void **)&back);
    show_str_arr(arr, "strings to four");
    int idx = arr->idx(arr, three);
    (idx == 2) ? printf("pass") : printf("fail");
    printf(" ptr idx 2 == %d \n", idx);

  	arr = crray_str_init();
    char hi[] = "hello";
    arr->add(arr, hi);
    arr->get(arr, 0, &back);
    strcmp(hi, back) ? printf("fail") : printf("pass");
    printf(" setting and getting string\n");

  	arr = crray_str_init();
    char *a = "alpha";
    char *b = "bravo";
    char *c = "charlie super duper long and fancy things";
    arr->add(arr, a);
    arr->add(arr, b);
    arr->add(arr, c);
    arr->get(arr, 0, &back);
    strcmp(a, back) ? printf("fail") : printf("pass");
    printf(" setting and getting string (a)\n");
    arr->get(arr, 1, &back);
    strcmp(b, back) ? printf("fail") : printf("pass");
    printf(" setting and getting string (b)\n");
    arr->get(arr, 2, &back);
    strcmp(c, back) ? printf("fail") : printf("pass");
    printf(" setting and getting string (c) '%s' vs '%s'\n", c, back);

}

void buff_tests(){
  char *hi = "hi";
  char *there = " there";
  char *hithere = "hi there";
  char *rest = " long fello with the scraggly beard.";
  char *sentence = "hi there long fello with the scraggly beard.";
  struct crowbuff *a = crowbuff_init();
  a->push(a, hi, strlen(hi));
  a->push(a, there, strlen(there));
  if(!strcmp(a->content, hithere))
    printf("pass");
  else
    printf("fail");
  printf(" hi combined into hi there\n");

  a->push(a, rest, strlen(rest));
  if(!strcmp(a->content, sentence))
    printf("pass");
  else
    printf("fail");
  printf(" buff sentence\n");
}

int main(int argc, char **argv){
    int_tests();
    ptr_tests();
    buff_tests();

/*

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

