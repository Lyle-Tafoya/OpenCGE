#ifndef _GRAPHICS_OPENGL_LEGACY_HPP
#define _GRAPHICS_OPENGL_LEGACY_HPP

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <OpenCGE/system.hpp>
#include <OpenCGE/components/graphics_3d.hpp>

namespace OpenCGE
{
  class GraphicsOpenGLLegacy : public System
  {
  public:
    GraphicsOpenGLLegacy(int window_width = 640, int window_height = 480, std::string const& window_name = "OpenCGE");
    void entityAdd(size_t entity_id);
    void entityRemove(size_t entity_id);
    void sceneLoad(std::string const& file_path);
    void scenesLoad(std::string const& directory_path);
    void sceneUpdate(nlohmann::json const& message);
    void shutdown(nlohmann::json const& message);
    void update(nlohmann::json const& message);
    void windowResize(int width, int height);

  private:
    std::unordered_map<size_t,Component::Graphics3D *> components;
    GLFWwindow *window;
    std::unordered_map<std::string, Field::Scene3D> scene_templates;
  };
}

#endif
