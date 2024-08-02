#include "object.hpp"

class Object
{
public:
  Object();
  // int id = 0;

  // void render();

private:
  SDL_Renderer *renderer = nullptr;
  // string type = "";
  bool dragging = false;
};

Object::Object()
{
  std::cout << "hellow" << std::endl;
}
