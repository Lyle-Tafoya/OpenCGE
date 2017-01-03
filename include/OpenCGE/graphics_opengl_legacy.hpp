#ifndef _GRAPHICS_OPENGL_LEGACY_HPP
#define _GRAPHICS_OPENGL_LEGACY_HPP

#include <OpenCGE/system.hpp>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <assimp/scene.h>
#include <unordered_map>
  using std::unordered_map;
#include <assimp/Importer.hpp>
  using Assimp::Importer;

namespace OpenCGE
{
  class GraphicsOpenGLLegacy : public System
  {
  public:
    GraphicsOpenGLLegacy();
    void sceneLoad(string const& file_path);
    void scenesLoad(string const& directory_path);
    void sceneUpdate(Json & message);
    void shutdown(Json & message);
    void update(Json & message);
    void windowResize(int width, int height);
  private:
    GLFWwindow *window;
    unordered_map<string, const aiScene *> scene_templates;
    Importer importer;
  };
}

#endif
