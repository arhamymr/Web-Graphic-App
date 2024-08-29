#include "app.hpp"

static App *instance = nullptr;

App::App(int width, int height)
{

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return;
  }
  window = SDL_CreateWindow("Canvas",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            width, height,
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

  obj = new Object(renderer);
  colors = new Colors();
  instance = this;
}

void App::pause()
{
  printf("pause\n");
  emscripten_pause_main_loop();
}

void App::resume()
{
  printf("resume\n");
  emscripten_resume_main_loop();
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

  // // Draw some shapes example for guide
  // thickLineColor(renderer, 10, 10, 60, 60, 5, 0xFF0FFFF0);
  // circleColor(renderer, 150, 40, 30, 0xFF00FF00);
  // arcColor(renderer, 250, 40, 30, 45, 200, 0xFF0000FF);
  // aacircleColor(renderer, 350, 40, 30, 0xFF00FF00);
  // filledCircleColor(renderer, 450, 40, 30, 0xFF00FFFF);
  // ellipseColor(renderer, 550, 40, 30, 10, 0xFF00FF00);
  // aaellipseColor(renderer, 50, 140, 30, 10, 0xFF00FF00);
  // filledEllipseColor(renderer, 150, 140, 30, 10, 0xFF00FF00);
  // pieColor(renderer, 250, 140, 30, -45, 45, 0xFF00FF00);
  // filledPieColor(renderer, 350, 140, 30, 45, -45, 0xFF00FF00);
  // aatrigonColor(renderer, 400, 140, 480, 140, 440, 170, 0xFF0FF0FF);

  // Sint16 ptx[] = {510, 590, 590, 550, 510};
  // Sint16 pty[] = {130, 130, 180, 150, 180};
  // aapolygonColor(renderer, ptx, pty, 5, 0xFF0F0F0F);

  // rectangleColor(renderer, 20, 210, 90, 260, 0xFF000000);
  // pixelColor(renderer, 150, 250, 0xFF0FA0A0);
  // boxColor(renderer, 220, 210, 290, 260, 0xFFCFBFAF);

  // characterColor(renderer, 350, 230, 'K', 0xFF0000FF);
  // stringColor(renderer, 450, 230, "LiTi & sesajad", 0xFFAABBCC);

  // // Draw filled and stroked rectangles
  // // Filled rectangle
  // boxColor(renderer, 320, 210, 390, 260, 0xFF00FF00);
  // // Stroked rectangle
  // rectangleColor(renderer, 320, 210, 390, 260, 0xFF000000);

  // Draw lines between consecutive points using Bresenham's line algorithm
  // Example line with brush stroke
  // Example line with brush stroke

  vector<SDL_Point> data_point = obj->getCurrentDataPoint();

  if (data_point.size() > 1)
  {
    for (int i = 0; i < data_point.size() - 1; i++)
    {
      // Set the drawing color (R, G, B, A)
      aalineRGBA(renderer, data_point[i].x, data_point[i].y, data_point[i + 1].x, data_point[i + 1].y, 255, 0, 0, 255);
    }
  }
  // // Draw filled and stroked circles
  // // Filled circle
  // filledCircleColor(renderer, 450, 300, 30, 0xFFFF0000);
  // // Stroked circle
  // circleColor(renderer, 450, 300, 30, 0xFF000000);

  // Draw a white line
  lineRGBA(renderer, 50, 50, 200, 200, 255, 255, 255, 255);

  // Draw a green rectangle
  rectangleRGBA(renderer, 300, 100, 400, 200, 0, 255, 0, 255);

  // Draw a filled blue circle
  filledCircleRGBA(renderer, 500, 300, 50, 0, 0, 255, 255);

  // Draw a yellow polygon
  Sint16 vx[4] = {100, 150, 200, 150};
  Sint16 vy[4] = {300, 250, 300, 350};
  filledPolygonRGBA(renderer, vx, vy, 4, 255, 255, 0, 255);

  obj->drawObject();
  obj->drawSelectIndicator();
  drawSelectRect();

  SDL_RenderPresent(renderer);
}

void App::loopWrapperForEmscripten()
{
  instance->appLoop();
}

void App::mainLoop()
{
  emscripten_set_main_loop(App::loopWrapperForEmscripten, 0, 1);
}

// Function to draw a line using Bresenham's line algorithm
void App::onMouseMotion(int x, int y)
{
  cout << "mouse move" << x << "-" << y << endl;
  mouseMoveX = x;
  mouseMoveY = y;

  if (mode == "draw")
  {
    if (isDrawline)
    {
      obj->addCurrentDataPoint({x, y});
    }
  }
}

void App::onMouseButtonDown(int button, int x, int y)
{
  mouseDownX = x;
  mouseDownY = y;

  isSelecting = true;

  if (mode == "select")
  {
    obj->draggingObject(x, y);
  }

  if (mode == "draw")
  {
    if (button == SDL_BUTTON_LEFT)
    {
      isDrawline = true;
      obj->clearCurrentDataPoint(); // Clear previous points
    }
  }
}

void App::onMouseButtonUp(int button, int x, int y)
{
  mouseUpX = x;
  mouseUpY = y;

  if (mode == "select")
  {
    obj->setSelectObject(x, y);
  }

  if (mode == "box")
  {
    int x1 = mouseDownX, y1 = mouseDownY;
    int x2 = mouseUpX, y2 = mouseUpY;
    int width = x2 - x1;
    int height = y2 - y1;

    printf("inside x1: %d, y1: %d, x2: %d, y2: %d, width: %d, height: %d\n", x1, y1, x2, y2, width, height);
    // Draw rectangle
    obj->addDataObject(
        {
            colors->getFill(),
            1,
            mouseDownX,
            mouseDownY,
            width,
            height,
        });
  }

  if (mode == "draw")
  {
    isDrawline = false;
  }

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
  case SDLK_a:
    obj->addDataObject(
        {
            colors->getFill(),
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

void App::activeDrawBox()
{
  mode = "box";
}

void App::activeSelect()
{
  mode = "select";
}

// draw
void App::activeDrawLine()
{
  mode = "draw";
}

// color

void App::setFill(string color)
{
  colors->setFill(color);
}

void App::setStroke(string color)
{
  colors->setStroke(color);
}