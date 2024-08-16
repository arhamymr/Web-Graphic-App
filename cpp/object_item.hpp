#ifndef OBJECT_ITEM_HPP
#define OBJECT_ITEM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cairo.h>
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
  ObjectItem(cairo_t *cr, vector<DataObject> *data);
  void draw_object();
  void hexToRGB(const string &hex, double &r, double &g, double &b);

private:
  vector<DataObject> *data_object;
  SDL_Renderer *renderer = nullptr;
  cairo_t *cr = nullptr;
};

#endif // OBJECT_ITEM_HPP