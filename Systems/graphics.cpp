#include <GL/glew.h>
#include "graphics.h"

namespace OpenCGE
{
  graphics::graphics(size_t w, size_t h, string winTitle)
    : pWindow(nullptr), title(winTitle), width(w), height(h) {}

  // Initialize our graphics system
  void graphics::Init()
  {
    // Use GLFW to create a window
    glfwInit();

    // Set the OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    glfwMakeContextCurrent(pWindow); // Initialize GLEW
    glewExperimental=true;
  }

  void graphics::Update(float delta)
  {
    glfwSwapBuffers(pWindow);
  }
}
