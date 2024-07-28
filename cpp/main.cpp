#include <stdio.h>
#include <emscripten/bind.h>

using namespace emscripten;

extern "C"
{
  void sayHi()
  {
    printf("Hi!\n");
  }
}

class MyClass
{
public:
  MyClass() {}
  void sayHi()
  {
    printf("Hi!\n");
  }
};

EMSCRIPTEN_BINDINGS(myClassExample)
{
  class_<MyClass>("MyClass")
      .constructor<>()
      .function("sayHi", &MyClass::sayHi);
}

int main()
{
  printf("hello, world!\n");
  return 0;
}