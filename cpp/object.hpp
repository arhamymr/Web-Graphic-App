#ifndef OBJECT_ITEM_HPP
#define OBJECT_ITEM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <SDL.h>

using namespace std;

struct DataObject
{

  string hexColor;

  int id, x, y, width, height;
  // int type;
  // bool isDragging;
};

class Object
{
public:
  Object(SDL_Renderer *renderer, vector<DataObject> *data);
  void drawObject();
  void hexToRGB(const string &hex, int &r, int &g, int &b);
  string randomColor();

private:
  vector<DataObject> *data_object;
  SDL_Renderer *renderer = nullptr;
};

#endif // OBJECT_ITEM_HPP