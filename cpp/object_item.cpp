#include "object_item.hpp"

ObjectItem::ObjectItem(cairo_t *r, vector<DataObject> *d)
{
  cr = r;
  data_object = d;
}

void ObjectItem::draw_object()
{

  for (const auto &obj : *data_object)
  {
    double r, g, b;
    hexToRGB(obj.hexColor, r, g, b);

    cairo_set_source_rgb(cr, r, g, b);
    cairo_rectangle(cr, static_cast<int>(obj.x), static_cast<int>(obj.y), static_cast<int>(obj.width), static_cast<int>(obj.height));

    cairo_set_source_rgb(cr, r, g, b);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_stroke(cr);
  };

  // cairo_set_source_rgb(cr, 0, 0, 0);
  // cairo_rectangle(cr, static_cast<int>(obj.x), static_cast<int>(obj.y), 100, 100);
  // cairo_stroke(cr);
}

// Function to convert hex color string to RGB components
void ObjectItem::hexToRGB(const std::string &hex, double &r, double &g, double &b)
{
  if (hex[0] == '#')
  {
    unsigned int hexValue = std::stoul(hex.substr(1), nullptr, 16);
    r = ((hexValue >> 16) & 0xFF) / 255.0;
    g = ((hexValue >> 8) & 0xFF) / 255.0;
    b = (hexValue & 0xFF) / 255.0;
  }
  else
  {
    throw std::invalid_argument("Invalid hex color format");
  }
}