#include <GLFW/glfw3.h>
#include "input.h"

namespace OpenCGE
{
  void Input::initialize()
  {

  }

  void Input::update(float delta)
  {
    glfwPollEvents();
  }
}
