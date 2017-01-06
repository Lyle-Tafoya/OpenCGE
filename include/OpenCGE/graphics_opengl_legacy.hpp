#ifndef _GRAPHICS_OPENGL_LEGACY_HPP
#define _GRAPHICS_OPENGL_LEGACY_HPP

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <OpenCGE/system.hpp>
#include <OpenCGE/components/point_3d.hpp>
#include <OpenCGE/components/scene_3d.hpp>

namespace OpenCGE
{
  class GraphicsOpenGLLegacy : public System
  {
  public:
    GraphicsOpenGLLegacy();
    static void * createPoint3D();
    static void * createScene3D();
    void sceneLoad(std::string const& file_path);
    void scenesLoad(std::string const& directory_path);
    void sceneUpdate(nlohmann::json const& message);
    void shutdown(nlohmann::json const& message);
    void update(nlohmann::json const& message);
    void windowResize(int width, int height);
  private:
    GLFWwindow *window;
    std::unordered_map<std::string, const aiScene *> scene_templates;
    Assimp::Importer importer;
  };
}

#endif
