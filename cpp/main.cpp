#include "app.hpp"

int main()
{
  App app(200, 220);
  app.mainLoop();

  app.quit();
  return 0;
}