#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "../crowx/crowx.c"
#include "../poly/poly.c"
#include "../tested/tested.c"
#include "../counted/counted.c"
#include "crray.c"

void print_out(Crray *arr){
  printf("-------- start -------------\n");
  for(int i=0;i<arr->length;i++){
    printf("%d:'%s'\n", i, arr->content[i]);
  }
}

void print_out_counted(Crray *arr){
  printf("-------- start -------------\n");
  for(int i=0;i<arr->length;i++){
    CtlCounted *c = arr->content[i];
    write(1, c->data, c->length); 
    write(1, "\n", 1); 
  }
}

int main(){
  Crray *arr = ctl_crray_alloc(1);
  char alpha[]="alcahol is nice";
  char bravo[]="beetles are nice and crunchy";
  char charlie[]="carrots and canalope";
  char delta[]="dentists are scary";
  char echo[]="escalith is for excellence";
  char foxtrot[]="freedom is over rated";
  char golf[]="green tomatoes and ham";

  ctl_crray_push(arr, (CtlAbs *)alpha, -1);
  handle_case(arr->length == 1, "first item has length 1", 
    arr->length, "");
  handle_case(arr->alloc_length == 4, "alloc size 4", 
    arr->alloc_length, "");

  ctl_crray_push(arr, (CtlAbs *)bravo, -1);
  ctl_crray_push(arr, (CtlAbs *)charlie, -1);
  ctl_crray_push(arr, (CtlAbs *)delta, -1);
  ctl_crray_push(arr, (CtlAbs *)echo, -1);
  handle_case(arr->length == 5, "fifth item has length 5", 
    arr->length, "");
  handle_case(arr->alloc_length == 8, "alloc size 8", 
    arr->alloc_length, "");
  printf("\x1b[0m");

  arr = ctl_crray_alloc(1);
  ctl_crray_push(arr, (CtlAbs *)alpha, -1);
  ctl_crray_push(arr, (CtlAbs *)bravo, -1);
  ctl_crray_push(arr, (CtlAbs *)charlie, 1);
  print_out(arr);
  handle_case(arr->length == 3, "after insert idx1 length 3", 
    arr->length, "");

  handle_case(arr->content[0] == alpha, "first elem is first", 
    arr->length, arr->content[0]);
  handle_case(arr->content[1] == charlie, "thrd elem elem is second", 
    arr->length, arr->content[1]);
  handle_case(arr->content[2] == bravo, "second elem elem is third", 
    arr->length, arr->content[2]);

  ctl_crray_push(arr, (CtlAbs *)delta, -1);
  ctl_crray_push(arr, (CtlAbs *)echo, -1);
  ctl_crray_push(arr, (CtlAbs *)foxtrot, -1);
  ctl_crray_push(arr, (CtlAbs *)golf, -1);
  print_out(arr);
  printf("remove 3\n");
  ctl_crray_remove(arr, 3);
  print_out(arr);
  printf("remove 0\n");
  ctl_crray_remove(arr, 0);
  print_out(arr);

  arr = ctl_crray_alloc(0);
  ctl_crray_push(arr, (CtlAbs *)ctl_counted_from_cstr("apple"), -1);
  ctl_crray_push(arr, (CtlAbs *)ctl_counted_from_cstr("bananna"), -1);
  ctl_crray_push(arr, (CtlAbs *)ctl_counted_from_cstr("carrot"), -1);
  CtlCounted *sep = ctl_counted_from_cstr(", ");

  CtlCounted *out = ctl_join(arr, sep);
  char ctl_join_out[] = "apple, bananna, carrot";
  int out_r = strcmp(ctl_join_out, out->data);
  handle_case(out_r == 0, "join results", out_r, "");

  Crray *splitout = ctl_split(ctl_counted_from_cstr("./usr/../local/../this/../../is/../rediculous"), ctl_counted_from_cstr("../"));
  handle_case(splitout->length == 6, "split by ../ results ", splitout->length, "");

  out_r = strcmp("./usr/", ((CtlCounted *)splitout->content[0])->data);
  handle_case(out_r == 0, "frst split results ", out_r, "");

  out_r = strcmp("local/", ((CtlCounted *)splitout->content[1])->data);
  handle_case(out_r == 0, "second split results ", out_r, "");

  out_r = strcmp("this/", ((CtlCounted *)splitout->content[2])->data);
  handle_case(out_r == 0, "third split results ", out_r, "");

  handle_case(((CtlCounted *)splitout->content[3])->length == 0, "fourth split results ", ((CtlCounted *)splitout->content[3])->length, "");

  out_r = strcmp("is/", ((CtlCounted *)splitout->content[4])->data);
  handle_case(out_r == 0, "fifth split results ", out_r, "");

  out_r = strcmp("rediculous", ((CtlCounted *)splitout->content[5])->data);
  handle_case(out_r == 0, "sixth split results ", out_r, "");

  splitout = ctl_split(ctl_counted_from_cstr("one/two/three"), ctl_counted_from_cstr("/"));
  print_out_counted(splitout);
  out_r = strcmp("one", ((CtlCounted *)splitout->content[0])->data);
  handle_case(out_r == 0, "frst simple / split results ", out_r, "");
  out_r = strcmp("two", ((CtlCounted *)splitout->content[1])->data);
  handle_case(out_r == 0, "frst simple / split results ", out_r, "");
  out_r = strcmp("three", ((CtlCounted *)splitout->content[2])->data);
  handle_case(out_r == 0, "frst simple / split results ", out_r, "");
}
