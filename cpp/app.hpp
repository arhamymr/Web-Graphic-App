#ifndef APP_HPP
#define APP_HPP

#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include "object.hpp"
#include "colors.hpp"
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace std;

class App
{
public:
  App(int width, int height);

  static void loopWrapperForEmscripten();
  void appLoop();
  void mainLoop();
  void appEvents();
  void pause();
  void resume();
  void quit();

  // draw
  void activeDrawLine();

  // input
  void onMouseMotion(int x, int y);
  void onMouseButtonDown(int button, int x, int y);
  void onMouseButtonUp(int button, int x, int y);
  void onKeyDown(int keyCode);

  // box
  void activeDrawBox();

  // select
  void activeSelect();
  void drawSelectRect();
  void drawDottedRect(const SDL_Rect &rect, int dotSpacing);

  // canvas
  void renderCanvas();
  void drawBackgroundGrid();

  // helpers
  void printVectorData(const DataObject &obj);

private:
  Object *obj;
  Colors *colors;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Texture *texture = nullptr;

  string mode = "select";
  bool isRunning = true;

  vector<DataObject> data_object;
  vector<SDL_Point> data_point;
  bool dragging = false;

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
  bool isDrawline = false;
};

#endif // APP_HPP