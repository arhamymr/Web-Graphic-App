#include <emscripten/bind.h>
#include "app.hpp"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(app_class)
{
  class_<App>("App")
      .constructor<>();
}
