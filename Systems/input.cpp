#include <GLFW/glfw3.h>
#include "input.h"

namespace OpenCGE
{
  void Input::Init()
  {

  }

  void Input::Update(float delta)
  {
    glfwPollEvents();
  }
}
