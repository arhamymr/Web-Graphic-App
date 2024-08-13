#include "app.hpp"

App::App()
{

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return;
  }
  window = SDL_CreateWindow("Canvas",
                            100,
                            100,
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

  width = 300;
  height = 300;

  canvas = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
  if (!canvas)
  {
    printf("Failed to create texture: %s\n", SDL_GetError());
    return;
  }

  SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
  SDL_RenderClear(renderer);
}

void App::mainLoop()
{

  bool running = true;

  SDL_Event event;

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

    // Set the texture as the render target
    SDL_SetRenderTarget(renderer, canvas);

    // Clear the texture with a white color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw a red rectangle on the texture
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = {50, 50, 400, 300};
    SDL_RenderFillRect(renderer, &rect);

    // Reset the render target to the default render target (the window)
    SDL_SetRenderTarget(renderer, NULL);

    // Copy the texture to the window renderer
    SDL_RenderCopy(renderer, canvas, NULL, NULL);

    // generate red box
    ObjectItem obj(renderer, &data_object);
    data_object.push_back({
        "#2d2d2d",
        1,
        50,
        50,
        100,
        100,
    });

    obj.draw_object();
    // Update screen
    SDL_RenderPresent(renderer);

    // Delay to limit frame rate
    SDL_Delay(16); // Approximately 60 frames per second
  }
}

void App::onMouseMotion(int x, int y)
{
  cout << "mouse move" << x << "-" << y << endl;
  mouseX = x;
  mouseY = y;
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
            "#2d2dab",
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

void App::quit()
{

  // quit sdl properly
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}