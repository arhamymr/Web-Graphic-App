#include <stdio.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>
#include <SDL.h>
#include <iostream>
// #include "object.hpp"

using namespace emscripten;
using namespace std;

class DesignTools
{
public:
  DesignTools()
  {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      printf("SDL_Init Error: %s\n", SDL_GetError());
      return;
    }
    int width, height;
    // Print the width and height
    printf("Canvas width: %d\n", width);
    printf("Canvas height: %d\n", height);

    emscripten_get_canvas_element_size("#canvas", &width, &height);
    window = SDL_CreateWindow("Canvas",
                              100,
                              100,
                              2000, 2000,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
      printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
      SDL_Quit();
      return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
      printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
      SDL_DestroyWindow(window);
      SDL_Quit();
      return;
    }

    // Register keyboard move callback
    emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, true, keyDownProxy);
    emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, true, keyUpProxy);

    // Register mouse event callbacks
    emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, true, mouse_down_callback);
    emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, true, mouse_move_callback);
    emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, true, mouse_up_callback);

    // Set the draw color to gray (RGB: 128, 128, 128)
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderClear(renderer);
  }

  // ~DesignTools()
  // {
  //   if (window)
  //   {
  //     SDL_DestroyWindow(window);
  //   }

  //   if (renderer)
  //   {
  //     SDL_DestroyRenderer(renderer);
  //   }
  //   SDL_Quit();
  // }

  void sayHi()
  {
    printf("Hi!\n");
  }

  void draw()
  {

    // Set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    SDL_RenderDrawRect(renderer, &rect);

    // Fill the rectangle
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    // ObjectItem obj;
  }

  void redraw()
  {
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
  }

  void main_loop()
  {
    instance = this;
    emscripten_set_main_loop(mainLoopProxy, 0, true);
  }

  // Key down event handler (non-static)
  void onKeyDown(int keyCode)
  {
    switch (keyCode)
    {
    case 38:
      rect.y -= 1 * SPEED;
      break;
    case 40:
      rect.y += 1 * SPEED;
      break;
    case 39:
      rect.x += 1 * SPEED;
      break;
    case 37:
      rect.x -= 1 * SPEED;
      break;
    }
    redraw();
    cout << "Key down: " << keyCode << endl;
  }

  // Key up event handler (non-static)
  void onKeyUp(int keyCode)
  {
    cout << "Key up: " << keyCode << endl;
  }

  // Static key down event proxy
  static EM_BOOL keyDownProxy(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData)
  {
    if (instance)
    {
      instance->onKeyDown(keyEvent->keyCode);
    }
    return EM_TRUE;
  }

  // Static key up event proxy
  static EM_BOOL keyUpProxy(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData)
  {
    if (instance)
    {
      instance->onKeyUp(keyEvent->keyCode);
    }
    return EM_TRUE;
  }

  static EM_BOOL mouse_down_callback(int eventType, const EmscriptenMouseEvent *e, void *userData)
  {
    DesignTools *tools = static_cast<DesignTools *>(userData);
    tools->on_mouse_down(e);
    return EM_TRUE;
  }

  static EM_BOOL mouse_move_callback(int eventType, const EmscriptenMouseEvent *e, void *userData)
  {
    DesignTools *tools = static_cast<DesignTools *>(userData);
    tools->on_mouse_move(e);
    return EM_TRUE;
  }

  static EM_BOOL mouse_up_callback(int eventType, const EmscriptenMouseEvent *e, void *userData)
  {
    DesignTools *tools = static_cast<DesignTools *>(userData);
    tools->on_mouse_up(e);
    return EM_TRUE;
  }

  void on_mouse_down(const EmscriptenMouseEvent *e)
  {
    dragging = true;
  }

  void on_mouse_move(const EmscriptenMouseEvent *e)
  {
    if (dragging)
    {
      rect.x = e->clientX - drag_offset_x;
      rect.y = e->clientY - drag_offset_y;
      redraw();
      cout << "move: " << e->clientX << e->clientY << endl;
    }
  }

  void on_mouse_up(const EmscriptenMouseEvent *e)
  {
    dragging = false;
  }

private:
  int SPEED = 10;
  static DesignTools *instance;
  bool dragging = false;
  static void mainLoopProxy()
  {
    if (instance)
    {
      instance->main_loop();
    }
  }
  int drag_offset_x = 0, drag_offset_y = 0;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  uint32_t ticksForNextKeyDown = 0;
  SDL_Rect rect = {.x = 10, .y = 10, .w = 150, .h = 100};
};
