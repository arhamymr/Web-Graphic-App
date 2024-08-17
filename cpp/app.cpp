#include "app.hpp"

static App *instance = nullptr;

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

  obj = new ObjectItem(renderer, &data_object);

  instance = this;
}

void App::appEvents()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      isRunning = false;
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
}

void App::appLoop()
{
  appEvents();
  // Clear the screen
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  obj->draw_object();
  drawSelectRect();

  SDL_RenderPresent(renderer);
}

void App::loopWrapperForEmscripten()
{
  instance->appLoop();
}

void App::mainLoop()
{

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(App::loopWrapperForEmscripten, 0, 1);
#else
  // init object item
  while (isRunning)
  {
    appLoop();

    // Delay to limit frame rate
    SDL_Delay(60);
  }
#endif
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

  printf("inside x1: %d, y1: %d, x2: %d, y2: %d, width: %d, height: %d\n", x1, y1, x2, y2, width, height);
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

void App::drawDottedRect(const SDL_Rect &rect, int dotSpacing)
{
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set the color for the dots

  // Draw top and bottom edges
  for (int x = rect.x; x < rect.x + rect.w; x += dotSpacing)
  {
    SDL_RenderDrawPoint(renderer, x, rect.y);              // Top edge
    SDL_RenderDrawPoint(renderer, x, rect.y + rect.h - 1); // Bottom edge
  }

  // Draw left and right edges
  for (int y = rect.y; y < rect.y + rect.h; y += dotSpacing)
  {
    SDL_RenderDrawPoint(renderer, rect.x, y);              // Left edge
    SDL_RenderDrawPoint(renderer, rect.x + rect.w - 1, y); // Right edge
  }
}

void App::drawSelectRect()
{
  if (isSelecting)
  {
    int x1 = mouseDownX, y1 = mouseDownY;
    int x2 = mouseMoveX, y2 = mouseMoveY;

    int width = x2 - x1;
    int height = y2 - y1;

    printf("x1: %d, y1: %d, x2: %d, y2: %d, width: %d, height: %d\n", x1, y1, x2, y2, width, height);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    selectRect.x = x1;
    selectRect.y = y1;
    selectRect.w = width;
    selectRect.h = height;

    drawDottedRect(selectRect, 5);
  }
}