#include<stdio.h>

void fun(int *main_local_addr){
   int fun_local;
   if (main_local_addr < &fun_local)
      printf("Stack grows upward");
   else
      printf("Stack grows downward");
}

int main(){
   int main_local;
   fun(&main_local);
   return 0;
}