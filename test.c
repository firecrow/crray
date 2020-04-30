#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "../crowx/crowx.c"
#include "../poly/poly.c"
#include "crray.c"

void handle_case(int pass_fail, char *msg, int val, char *example){
  if(pass_fail){
    printf("\x1b[32mPASS:");
  }else{
    printf("\x1b[32mFAIL:");
  }
  printf("%s val:%d, example:%s\x1b[0m\n", msg, val, example);
}

void print_out(struct ptrarray *arr){
  printf("-------- start -------------\n");
  int i;
  for(i=0;i<arr->length;i++){
    printf("%d:'%s'\n", i, arr->content[i]);
  }
}

int main(){
  struct ptrarray *arr = ptrarray_alloc(1);
  char alpha[]="alcahol is nice";
  char bravo[]="beetles are nice and crunchy";
  char charlie[]="carrots and canalope";
  char delta[]="dentists are scary";
  char echo[]="escalith is for excellence";
  char foxtrot[]="freedom is over rated";
  char golf[]="green tomatoes and ham";

  arr_push(arr, (struct abstract *)alpha, -1);
  handle_case(arr->length == 1, "first item has length 1", 
    arr->length, "");
  handle_case(arr->alloc_length == 4, "alloc size 4", 
    arr->alloc_length, "");

  arr_push(arr, (struct abstract *)bravo, -1);
  arr_push(arr, (struct abstract *)charlie, -1);
  arr_push(arr, (struct abstract *)delta, -1);
  arr_push(arr, (struct abstract *)echo, -1);
  handle_case(arr->length == 5, "fifth item has length 5", 
    arr->length, "");
  handle_case(arr->alloc_length == 8, "alloc size 8", 
    arr->alloc_length, "");
  printf("\x1b[0m");

  arr = ptrarray_alloc(1);
  arr_push(arr, (struct abstract *)alpha, -1);
  arr_push(arr, (struct abstract *)bravo, -1);
  arr_push(arr, (struct abstract *)charlie, 1);
  print_out(arr);
  handle_case(arr->length == 3, "after insert idx1 length 3", 
    arr->length, "");

  handle_case(arr->content[0] == alpha, "first elem is first", 
    arr->length, arr->content[0]);
  handle_case(arr->content[1] == charlie, "thrd elem elem is second", 
    arr->length, arr->content[1]);
  handle_case(arr->content[2] == bravo, "second elem elem is third", 
    arr->length, arr->content[2]);

  arr_push(arr, (struct abstract *)delta, -1);
  arr_push(arr, (struct abstract *)echo, -1);
  arr_push(arr, (struct abstract *)foxtrot, -1);
  arr_push(arr, (struct abstract *)golf, -1);
  print_out(arr);
  printf("remove 3\n");
  arr_remove(arr, 3);
  print_out(arr);
  printf("remove 0\n");
  arr_remove(arr, 0);
  print_out(arr);
}
