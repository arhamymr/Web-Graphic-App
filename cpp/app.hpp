#ifndef APP_HPP
#define APP_HPP

#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include "object_item.hpp"

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;

class App
{
public:
  App();
  void mainLoop();
  void onMouseMotion(int x, int y);
  void onMouseButtonDown(int button, int x, int y);
  void renderCanvas();
  void onKeyDown(int keyCode);
  void quit();

private:
  vector<DataObject> data_object;
  int SPEED = 10;
  bool dragging = false;

  SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  float canvas_zoom = 1.0f;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  int width;
  int height;
  SDL_Texture *canvas = nullptr;

  int mouseX = 0;
  int mouseY = 0;
};

#endif // APP_HPP