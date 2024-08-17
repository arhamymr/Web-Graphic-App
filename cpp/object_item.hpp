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

class ObjectItem
{
public:
  ObjectItem(SDL_Renderer *renderer, vector<DataObject> *data);
  void draw_object();
  void hexToRGB(const string &hex, int &r, int &g, int &b);

private:
  vector<DataObject> *data_object;
  SDL_Renderer *renderer = nullptr;
};

#endif // OBJECT_ITEM_HPP