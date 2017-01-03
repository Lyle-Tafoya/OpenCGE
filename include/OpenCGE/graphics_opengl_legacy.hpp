#ifndef _GRAPHICS_OPENGL_LEGACY_HPP
#define _GRAPHICS_OPENGL_LEGACY_HPP

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <OpenCGE/system.hpp>

namespace OpenCGE
{
  class GraphicsOpenGLLegacy : public System
  {
  public:
    GraphicsOpenGLLegacy();
    void sceneLoad(std::string const& file_path);
    void scenesLoad(std::string const& directory_path);
    void sceneUpdate(Json & message);
    void shutdown(Json & message);
    void update(Json & message);
    void windowResize(int width, int height);
  private:
    GLFWwindow *window;
    std::unordered_map<std::string, const aiScene *> scene_templates;
    Assimp::Importer importer;
  };
}

#endif
