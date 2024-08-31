#include "object.hpp"

Object::Object(SDL_Renderer *r)
{
  renderer = r;
}

// draw

void Object::drawSelectIndicator()
{
  for (const auto &obj : data_object)
  {
    if (obj.isSelected)
    {
      // Set the stroke color (e.g., red)
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

      SDL_Rect topLeftKnob = createKnob(obj.x, obj.y);
      SDL_RenderDrawRect(renderer, &topLeftKnob);

      SDL_Rect topRightKnob = createKnob(obj.x + obj.width, obj.y);
      SDL_RenderDrawRect(renderer, &topRightKnob);

      SDL_Rect bottomleftKnob = createKnob(obj.x, obj.y + obj.height);
      SDL_RenderDrawRect(renderer, &bottomleftKnob);

      SDL_Rect bottomRightKnob = createKnob(obj.x + obj.width, obj.y + obj.height);
      SDL_RenderDrawRect(renderer, &bottomRightKnob);

      // Define the outer stroke rectangle
      SDL_Rect outerRect;
      outerRect.x = obj.x - 1; // Adjust for stroke width
      outerRect.y = obj.y - 1;
      outerRect.w = obj.width + 2;
      outerRect.h = obj.height + 2;

      // Draw the outer stroke
      SDL_RenderDrawRect(renderer, &outerRect);
    }
  }
}

void Object::drawObject()
{

  for (const auto &obj : data_object)
  {
    int r, g, b;
    hexToRGB(obj.hexColor, r, g, b);
    // Set the drawing color
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    SDL_Rect rect;
    rect.x = obj.x; // Assuming obj has x and y members for position
    rect.y = obj.y;
    rect.w = obj.width; // Assuming obj has width and height members
    rect.h = obj.height;

    // Draw the rectangle
    SDL_RenderFillRect(renderer, &rect);
  };
}

void Object::hexToRGB(const std::string &hex, int &r, int &g, int &b)
{
  if (hex[0] == '#')
  {
    unsigned int hexValue = std::stoul(hex.substr(1), nullptr, 16);
    r = (hexValue >> 16) & 0xFF;
    g = (hexValue >> 8) & 0xFF;
    b = hexValue & 0xFF;
  }
  else
  {
    throw std::invalid_argument("Invalid hex color format");
  }
}

string Object::randomColor()
{
  string hexColor = "#";
  for (int i = 0; i < 6; i++)
  {
    hexColor += "0123456789ABCDEF"[rand() % 16];
  }

  return hexColor;
}

void Object::addDataObject(DataObject obj)
{
  obj.isSelected = false;
  data_object.push_back(obj);
}

void Object::removeDataObject(int id)
{
  // doing remove data object
}

void Object::removeLastDataObject()
{
  data_object.pop_back();
}

void Object::clearDataObject()
{
  data_object.clear();
}

vector<SDL_Point> Object::getCurrentDataPoint()
{
  return current_data_point;
}

void Object::addCurrentDataPoint(SDL_Point point)
{
  current_data_point.push_back(point);
}

void Object::clearCurrentDataPoint()
{
  current_data_point.clear();
}

// select object

SDL_Rect Object::createKnob(int x, int y)
{
  SDL_Rect knobRect;
  knobRect.x = x - 5;
  knobRect.y = y - 5;
  knobRect.w = 10;
  knobRect.h = 10;
  return knobRect;
}

void Object::setSelectObject(int x, int y)
{
  for (auto &obj : data_object)
  {
    if (x >= obj.x && x <= obj.x + obj.width && y >= obj.y && y <= obj.y + obj.height)
    {
      obj.isSelected = true;
    }
    else
    {
      obj.isSelected = false;
    }
  }
}

void Object::setDragOffset(int x, int y)
{
  for (auto &obj : data_object)
  {
    if (obj.isSelected)
    {
      dragOffset.x = x - obj.x;
      dragOffset.y = y - obj.y;
    }
  }
}

void Object::draggingObject(int x, int y)
{
  for (auto &obj : data_object)
  {
    if (obj.isSelected)
    {
      obj.x = x - dragOffset.x;
      obj.y = y - dragOffset.y;
    }
  }
}

bool Object::isInsideObject(int x, int y, DataObject obj)
{
  if (x >= obj.x && x <= obj.x + obj.width && y >= obj.y && y <= obj.y + obj.height)
  {
    return true;
  }
  return false;
}

void Object::handleMouseHover(int x, int y)
{

  for (auto &obj : data_object)
  {

    if (isInsideObject(x, y, obj))
    {
      if (obj.isSelected)
      {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
        break;
      }
    }
    else
    {
      SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    }
  }
}