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

    // TODO Compile report of all input recieved and send out messages to registered controller components for each one
  }
}
