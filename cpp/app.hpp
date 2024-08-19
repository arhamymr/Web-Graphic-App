#ifndef APP_HPP
#define APP_HPP

#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include "object_item.hpp"

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
  void drawLine(int x1, int y1, int x2, int y2, string color);

  // color
  void setSelectFillColor(string color);
  void setSelectStrokeColor(string color);

  // input
  void onMouseMotion(int x, int y);
  void onMouseButtonDown(int button, int x, int y);
  void onMouseButtonUp(int button, int x, int y);
  void onKeyDown(int keyCode);

  // aid
  void drawSelectRect();
  void drawDottedRect(const SDL_Rect &rect, int dotSpacing);
  void renderCanvas();
  void drawBackgroundGrid();

  // helpers
  void printVectorData(const DataObject &obj);

private:
  int screen_width = 1200;
  int screen_height = 900;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Texture *texture = nullptr;
  ObjectItem *obj;
  bool isRunning = true;

  vector<DataObject> data_object;
  int SPEED = 10;
  bool dragging = false;

  SDL_Rect camera = {0, 0, screen_width, screen_height};
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
  bool isDrawline = false;

  // color
  string selectFillColor = "#000000";
  string selectStrokeColor = "#000000";
};

#endif // APP_HPP