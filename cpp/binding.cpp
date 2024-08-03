#include <emscripten/bind.h>
#include "app.hpp"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(app_class)
{
  class_<App>("App")
      .constructor<>()
      .function("main_loop", &App::main_loop)
      .function("draw", &App::draw);
}
