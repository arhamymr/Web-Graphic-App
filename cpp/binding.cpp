#include <emscripten/bind.h>
#include "app.hpp"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(app_class)
{
  class_<App>("App")
      .constructor<>()
      .function("main_loop", &App::mainLoop)
      .function("draw", &App::renderCanvcas);

}
