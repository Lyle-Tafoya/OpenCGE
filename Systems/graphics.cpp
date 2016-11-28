#include <GL/glew.h>
#include "graphics.hpp"

namespace OpenCGE
{
  Graphics::Graphics(size_t w, size_t h, string winTitle)
    : pWindow(nullptr), title(winTitle), width(w), height(h) {}

  Graphics::~Graphics()
  {
    glfwTerminate();
  }

  // Initialize our graphics system
  void Graphics::initialize()
  {
    // Initialize window hints to default
    glfwInit();

    // Set the OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    glfwMakeContextCurrent(pWindow); // Initialize GLEW
    glewExperimental=true;
  }

  void Graphics::update(float delta)
  {
    glfwSwapBuffers(pWindow);
  }
}
