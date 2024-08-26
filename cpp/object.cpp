#include "object.hpp"

Object::Object(SDL_Renderer *r)
{
  renderer = r;
}

void Object::drawObject()
{

  for (const auto &obj : data_object)
  {
    int r, g, b;
    hexToRGB(obj.hexColor, r, g, b);
    // Set the drawing color
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    // Define the rectangle
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