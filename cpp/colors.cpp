#include "colors.hpp"

void Colors::setFill(string color)
{
  fill = color;
}

void Colors::setStroke(string color)
{
  stroke = color;
}

string Colors::getFill()
{
  return fill;
}

string Colors::getStroke()
{
  return stroke;
}