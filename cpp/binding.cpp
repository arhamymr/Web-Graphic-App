#include <emscripten/bind.h>
#include "app.hpp"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(app_class)
{
  class_<App>("App")
      .constructor<int, int>()
      .function("mainLoop", &App::mainLoop)
      .function("resume", &App::resume)
      .function("pause", &App::pause)
      .function("setSelectFillColor", &App::setSelectFillColor)
      .function("setSelectStrokeColor", &App::setSelectStrokeColor)
      .function("getSelectFillColor", &App::getSelectFillColor)
      .function("getSelectStrokeColor", &App::getSelectStrokeColor);
}
