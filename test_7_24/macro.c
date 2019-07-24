#include <stdlib.h>
#include <stdio.h>
 
#define MACRO1(x) (++(x))
#define MACRO2(x) (MACRO1(x)+100)
#define MACRO3(x) (MACRO2(x)+200)
 
int main(void)
{
  int a = 0;
  int b = 0;
  b = MACRO3(a);
  printf("%d\n", b);
  return 0;
}
