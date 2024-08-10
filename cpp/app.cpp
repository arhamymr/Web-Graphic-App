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

  // default canvas
  canvas = {10, 10, 500, 600};
  // Set the draw color to gray (RGB: 128, 128, 128)
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

    // Set the draw color to gray (RGB: 128, 128, 128)
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderClear(renderer); // Clear the screen with white color

    // Set the drawing color to red for the object
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Adjust the object's position based on the camera position and zoom
    SDL_Rect renderQuadCanvas = {
        static_cast<int>((canvas.x - camera.x) * canvas_zoom),
        static_cast<int>((canvas.y - camera.y) * canvas_zoom),
        static_cast<int>(canvas.w * canvas_zoom),
        static_cast<int>(canvas.h * canvas_zoom)};

    // Render the object
    SDL_RenderFillRect(renderer, &renderQuadCanvas);

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
}

void App::onMouseButtonDown(int button, int x, int y)
{
  if (button == SDL_BUTTON_LEFT)
  {
    cout << "clicked left" << x << "-" << y << endl;
    data_object.push_back(
        {
            "#2d2dab",
            1,
            static_cast<int>((x - camera.x) * canvas_zoom),
            static_cast<int>((y - camera.y) * canvas_zoom),
            static_cast<int>(200 * canvas_zoom),
            static_cast<int>(200 * canvas_zoom),
        });
  }
  else if (button == SDL_BUTTON_RIGHT)
  {
    cout << "clicked right" << x << "-" << y << endl;
  }
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