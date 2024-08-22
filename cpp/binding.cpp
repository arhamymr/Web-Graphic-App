#include <emscripten/bind.h>
#include "app.hpp"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(app_class)
{
  class_<App>("App")
      .constructor<int, int>()
      .function("mainLoop", &App::mainLoop)
      .function("drawBackgroundGrid", &App::drawBackgroundGrid)
      .function("resume", &App::resume)
      .function("pause", &App::pause)
      .function("activeSelect", &App::activeSelect)
      .function("activeDrawLine", &App::activeDrawLine)
      .function("activeDrawBox", &App::activeDrawBox);
}

EMSCRIPTEN_BINDINGS(color_class)
{
  class_<Colors>("Colors")
      .constructor()
      .function("setFill", &Colors::setFill)
      .function("setStroke", &Colors::setStroke);
};
