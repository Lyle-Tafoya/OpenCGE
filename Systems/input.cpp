#include "input.hpp"

#include <GLFW/glfw3.h>

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
