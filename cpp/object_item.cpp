#include "object_item.hpp"

ObjectItem::ObjectItem(SDL_Renderer *r, vector<DataObject> *d)
{
  renderer = r;
  data_object = d;
}

void ObjectItem::draw_object()
{

  for (const auto &obj : *data_object)
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

void ObjectItem::hexToRGB(const std::string &hex, int &r, int &g, int &b)
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