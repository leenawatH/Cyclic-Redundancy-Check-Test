#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
  int ran,upper = 10,lower = 1;
  srand(time(0));
  int n = (rand() % (upper - lower +1)) + lower;
  printf("%d",n);
}