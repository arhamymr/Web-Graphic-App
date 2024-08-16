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

  surface = SDL_CreateRGBSurface(
      0,
      SCREEN_WIDTH,
      SCREEN_HEIGHT, 32,
      0x00FF0000, /* Rmask */
      0x0000FF00, /* Gmask */
      0x000000FF, /* Bmask */
      0);         /* Amask */

  texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_LockSurface(surface);

  cairo_surface = cairo_image_surface_create_for_data((unsigned char *)surface->pixels, CAIRO_FORMAT_RGB24, surface->w, surface->h, surface->pitch);

  if (cairo_surface == nullptr)
  {
    printf("cairo_image_surface_create_for_data Error: %s\n", SDL_GetError());
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
  }

  cr = cairo_create(cairo_surface);

  if (cairo_status(cr) != CAIRO_STATUS_SUCCESS)
  {
    printf("cairo_create Error: %s\n", SDL_GetError());
    cairo_surface_destroy(cairo_surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
  }

  SDL_UnlockSurface(surface);
}

void App::mainLoop()
{

  bool running = true;

  SDL_Event event;

  // White background with cairo API
  cairo_set_source_rgba(cr, 1, 1, 1, 1.0);
  cairo_rectangle(cr, 0, 0, surface->w, surface->h);
  cairo_fill(cr);

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
      }
    }

    // // Clear the texture with a white color
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderClear(renderer);

    // // generate red box
    ObjectItem obj(cr, &data_object);

    obj.draw_object();
    // Update screen

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Delay to limit frame rate
    SDL_Delay(60); // Approximately 60 frames per second
  }
}

void App::onMouseMotion(int x, int y)
{
  cout << "mouse move" << x << "-" << y << endl;
  mouseX = x;
  mouseY = y;

  for (const auto &data : data_object)
  {
    printVectorData(data);
  }
}

void App::onMouseButtonDown(int button, int x, int y)
{
  if (button == SDL_BUTTON_LEFT)
  {
    cout << "clicked left" << x << "-" << y << endl;
  }
  else if (button == SDL_BUTTON_RIGHT)
  {
    cout << "clicked right" << x << "-" << y << endl;
  }
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
            mouseX,
            mouseY,
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

  if (cr)
    cairo_destroy(cr);
  if (cairo_surface)
    cairo_surface_destroy(cairo_surface);
  if (texture)
    SDL_DestroyTexture(texture);
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Quit();
}