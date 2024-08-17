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
  void onMouseButtonUp(int button, int x, int y);
  void renderCanvas();
  void drawBackgroundGrid();
  void onKeyDown(int keyCode);
  void printVectorData(const DataObject &obj);
  void quit();

private:
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Texture *texture = nullptr;
  SDL_Surface *surface = nullptr;

  vector<DataObject> data_object;
  int SPEED = 10;
  bool dragging = false;

  SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  float canvas_zoom = 1.0f;

  // current mouse position
  int mouseMoveX = 0;
  int mouseMoveY = 0;
  int mouseUpX = 0;
  int mouseUpY = 0;
  int mouseDownX = 0;
  int mouseDownY = 0;

  // select aid
  SDL_Rect selectRect = {0, 0, 0, 0};
  bool isSelecting = false;
};

#endif // APP_HPP