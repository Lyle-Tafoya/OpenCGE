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
    static GLFWwindow *get(const glm::ivec2 &windowDimensions=glm::ivec2(640, 480), const std::string &windowName="")
    {
      if(window != nullptr) { return window; }

      glfwInit();
      window = glfwCreateWindow(windowDimensions.x, windowDimensions.y, windowName.c_str(), NULL, NULL);

      return window;
    }

  private:
    static GLFWwindow *window;
  };

  GLFWwindow *GLFWSingleton::window = nullptr;
}

#endif
