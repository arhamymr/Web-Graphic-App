#include "object_item.hpp"

class ObjectItem
{
public:
  ObjectItem();
  // int id = 0;

  // void render();

private:
  SDL_Renderer *renderer = nullptr;
  // string type = "";
  bool dragging = false;
};

ObjectItem::ObjectItem()
{
  cout << "hellow" << endl;
}
