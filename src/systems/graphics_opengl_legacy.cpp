#include <OpenCGE/graphics_opengl_legacy.hpp>
#include <GL/glu.h>

namespace OpenCGE
{

  GraphicsOpenGLLegacy::GraphicsOpenGLLegacy()
  {
    componentsRegister({"orientation", "position", "scene_3d"});
    System::callbackRegister("scene_update", &GraphicsOpenGLLegacy::sceneUpdate, this);
    System::callbackRegister("shutdown", &GraphicsOpenGLLegacy::shutdown, this);
    System::callbackRegister("time_passed", &GraphicsOpenGLLegacy::update, this);

    glfwInit();
    window = glfwCreateWindow(640, 480, "OpenCGE", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    windowResize(width, height);
  }

  void GraphicsOpenGLLegacy::windowResize(int width, int height)
  {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, width/height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.f, 0.f, 5.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
  }

  void GraphicsOpenGLLegacy::modelLoad(string const& file_path)
  {
  }

  void GraphicsOpenGLLegacy::modelsLoad(string const& directory_path)
  {
  }

  void GraphicsOpenGLLegacy::sceneUpdate(json const& message)
  {
  }

  void GraphicsOpenGLLegacy::update(json const& message)
  {
    glfwSwapBuffers(window);
  }

  void GraphicsOpenGLLegacy::shutdown(json const& message)
  {
    glfwTerminate();
  }
}
