#ifndef OBJECT_ITEM_HPP
#define OBJECT_ITEM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <SDL.h>

using namespace std;

enum class ObjectType
{
  LINE = 0,
  BOX = 1,
  CIRCLE = 2,
  TEXT = 3
};

struct DataObject
{

  string hexColor;
  int id, x, y, width, height;
  ObjectType type;
  bool isSelected;
};

class Object
{
public:
  Object(SDL_Renderer *renderer);

  // draw
  void drawSelectIndicator();
  void drawObject();
  void hexToRGB(const string &hex, int &r, int &g, int &b);
  string randomColor();

  // object
  void addDataObject(DataObject obj);
  void removeDataObject(int id);
  void removeLastDataObject();
  void clearDataObject();

  // add current data point
  void addCurrentDataPoint(SDL_Point point);
  void clearCurrentDataPoint();
  vector<SDL_Point> getCurrentDataPoint();

  // select, hover, dragging
  SDL_Rect createKnob(int x, int y);
  bool isHoverObject(int x, int y, DataObject obj);
  void handleMouseHover(int x, int y);
  bool isInsideObject(int x, int y, DataObject obj);
  void draggingObject(int x, int y);
  void setDragOffset(int x, int y);
  void setSelectObject(int x, int y);

private:
  vector<DataObject> data_object;
  vector<SDL_Point> current_data_point;

  SDL_Renderer *renderer = nullptr;
  SDL_Point dragOffset = {0, 0};
};

#endif // OBJECT_ITEM_HPP