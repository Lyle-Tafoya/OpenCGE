#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <string>
  using std::string;
#include <GLFW/glfw3.h>

#include "../Engine/system.h"
#include "../Components/drawable.h"

namespace OpenCGE
{
  class GraphicsLegacy : public System
  {
    void Init();
    void Update(float delta);

    GLFWwindow *pWindow;
    string title; // The title of the window
    size_t width;
    size_t height;

  public:
    GraphicsLegacy(size_t w, size_t h, string winTitle);
  };
}

#endif