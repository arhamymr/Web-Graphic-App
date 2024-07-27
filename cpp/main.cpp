#include <stdio.h>

extern "C"
{
  void sayHi()
  {
    printf("Hi!\n");
  }
}

int main()
{
  printf("hello, world!\n");
  return 0;
}