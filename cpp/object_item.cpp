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
    Uint8 r, g, b;
    hexToRGB(obj.hexColor, r, g, b);
    SDL_Rect obj_rect = {static_cast<int>(obj.x), static_cast<int>(obj.y), static_cast<int>(obj.width), static_cast<int>(obj.height)};

    // Render the rectangle
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    SDL_RenderFillRect(renderer, &obj_rect);
  };
}

// Function to convert hex color string to RGB components
void ObjectItem::hexToRGB(const std::string &hex, Uint8 &r, Uint8 &g, Uint8 &b)
{
  if (hex[0] == '#')
  {
    stringstream ss;
    ss << std::hex << hex.substr(1);
    unsigned int hexValue;
    ss >> hexValue;

    r = (hexValue >> 16) & 0xFF;
    g = (hexValue >> 8) & 0xFF;
    b = hexValue & 0xFF;
  }
}