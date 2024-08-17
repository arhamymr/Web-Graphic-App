#include "app.hpp"

App::App()
{

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return;
  }
  window = SDL_CreateWindow("Canvas",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            SCREEN_WIDTH, SCREEN_HEIGHT,
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
}

void App::mainLoop()
{

  bool running = true;

  SDL_Event event;

  // init object item
  ObjectItem obj(renderer, &data_object);

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_KEYDOWN:
        onKeyDown(event.key.keysym.sym);
        break;
      case SDL_MOUSEMOTION:
        onMouseMotion(event.motion.x, event.motion.y);
        break;
      case SDL_MOUSEBUTTONDOWN:
        onMouseButtonDown(event.button.button, event.button.x, event.button.y);
        break;
      case SDL_MOUSEBUTTONUP:
        dragging = false;
        onMouseButtonUp(event.button.button, event.button.x, event.button.y);
        break;
      }
    }

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    obj.draw_object();

    if (isSelecting)
    {
      int x1 = mouseDownX, y1 = mouseDownY;
      int x2 = mouseMoveX, y2 = mouseMoveY;
      int width = x2 - x1;
      int height = y2 - y1;

      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

      selectRect.x = x1;
      selectRect.y = y1;
      selectRect.w = width;
      selectRect.h = height;

      // Draw the rectangle
      SDL_RenderDrawRect(renderer, &selectRect);
    }

    SDL_RenderPresent(renderer);

    // Delay to limit frame rate
    SDL_Delay(60);
  }
}

void App::onMouseMotion(int x, int y)
{
  cout << "mouse move" << x << "-" << y << endl;
  mouseMoveX = x;
  mouseMoveY = y;

  // for (const auto &data : data_object)
  // {
  //   printVectorData(data);
  // }
}

void App::onMouseButtonDown(int button, int x, int y)
{
  mouseDownX = x;
  mouseDownY = y;

  isSelecting = true;
}

void App::onMouseButtonUp(int button, int x, int y)
{
  mouseUpX = x;
  mouseUpY = y;
  if (button == SDL_BUTTON_LEFT)
  {
    cout << "clicked left" << x << "-" << y << endl;
  }
  else if (button == SDL_BUTTON_RIGHT)
  {
    cout << "clicked right" << x << "-" << y << endl;
  }

  int x1 = mouseDownX, y1 = mouseDownY;
  int x2 = mouseUpX, y2 = mouseUpY;
  int width = x2 - x1;
  int height = y2 - y1;

  // Draw rectangle
  data_object.push_back(
      {
          "#2d2d2d",
          1,
          mouseDownX,
          mouseDownY,
          width,
          height,
      });

  isSelecting = false;
}

void App::renderCanvas()
{
  // todo
}

void App::onKeyDown(int keyCode)
{
  switch (keyCode)
  {
  case SDLK_UP:
    camera.y -= SPEED;
    break;
  case SDLK_DOWN:
    camera.y += SPEED;
    break;
  case SDLK_LEFT:
    camera.x -= SPEED;
    break;
  case SDLK_RIGHT:
    camera.x += SPEED;
    break;
  case SDLK_LEFTBRACKET:
    canvas_zoom *= 1.1f;
    break;
  case SDLK_RIGHTBRACKET:
    canvas_zoom /= 1.1f;
    break;
  case SDLK_a:
    data_object.push_back(
        {
            "#2d2d2d",
            1,
            mouseMoveX,
            mouseMoveY,
            200,
            200,
        });
    break;
  }
  // Update screen
  SDL_RenderPresent(renderer);
}

void App::printVectorData(const DataObject &obj)
{
  cout << "Current vector data:" << std::endl;
  cout << ", ID: " << obj.id
       << ", X: " << obj.x
       << ", Y: " << obj.y
       << ", Width: " << obj.width
       << ", Height: " << obj.height
       << std::endl;
}

void App::quit()
{
  if (texture)
    SDL_DestroyTexture(texture);
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Quit();
}

void App::drawBackgroundGrid()
{
  // todo
}