#include <stdio.h>

extern "C"
{
  void sayHi()
  {
    printf("Hi!\n");
  }
}

void hello_world()
{
  printf("hello, world! from main function \n");
}

int main()
{
  printf("hello, world!\n");
  return 0;
}