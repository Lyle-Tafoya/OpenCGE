#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <string>
  using std::string;
#include <GLFW/glfw3.h>

#include "../Engine/system.h"
#include "../Components/drawable.h"

namespace OpenCGE
{
  // Handle OpenGL 3.0+ graphics with GLFW
  class Graphics : public System
  {
    void Init();
    void Update(float delta);

    GLFWwindow *pWindow;
    string title; // The title of the window

    // Window dimensions
    size_t width;
    size_t height;

  public:
    Graphics(size_t w, size_t h, string winTitle);
    ~Graphics();
  };
}

#endif
