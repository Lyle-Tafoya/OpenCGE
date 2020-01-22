#ifndef OPENCGE_GLFW_SINGLETON_HPP_
#define OPENCGE_GLFW_SINGLETON_HPP_

#include <string>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace OpenCGE
{
  class GLFWSingleton
  {
  public:
    static GLFWwindow *get()
    {
      if(window == nullptr)
      {
        glfwInit();
        window = glfwCreateWindow(640, 480, "OpenCGE", NULL, NULL);
      }

      return window;
    }

  private:
    static GLFWwindow *window;
  };

  GLFWwindow *GLFWSingleton::window = nullptr;
}

#endif
