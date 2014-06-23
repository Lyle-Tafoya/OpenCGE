#include <GL/glew.h>
#include "graphics_legacy.h"

namespace OpenCGE
{
  GraphicsLegacy::GraphicsLegacy(size_t w, size_t h, string winTitle)
    : pWindow(nullptr), title(winTitle), width(w), height(h) {}

  // Initialize our graphics system
  void GraphicsLegacy::Init()
  {
    // Use GLFW to create a window
    glfwInit();

    // Legacy support for OpenGL versions as far back as 2.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    glfwMakeContextCurrent(pWindow); // Initialize GLEW
    glewExperimental=true;
  }

  void GraphicsLegacy::Update(float delta)
  {
    glfwSwapBuffers(pWindow);
  }
}
