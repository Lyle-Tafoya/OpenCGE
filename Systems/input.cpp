#include <GLFW/glfw3.h>
#include "input.h"

namespace OpenCGE
{
  void input::Init()
  {

  }

  void input::Update(float delta)
  {
    glfwPollEvents();
  }
}
