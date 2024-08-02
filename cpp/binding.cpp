#include <emscripten/bind.h>
#include "app.hpp"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(design_tools_class)
{
  class_<DesignTools>("DesignTools")
      .constructor<>()
      .function("main_loop", &DesignTools::main_loop)
      .function("draw", &DesignTools::draw);
}
