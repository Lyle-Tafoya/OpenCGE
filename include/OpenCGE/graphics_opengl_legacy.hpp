#ifndef OPENCGE_GRAPHICS_OPENGL_LEGACY_HPP_
#define OPENCGE_GRAPHICS_OPENGL_LEGACY_HPP_

#include <filesystem>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include <OpenCGE/system.hpp>
#include <OpenCGE/components/graphics_3d.hpp>

namespace OpenCGE
{
  class GraphicsOpenGLLegacy : public System
  {
  public:
    GraphicsOpenGLLegacy(glm::ivec2 windowDimensions = glm::ivec2(640, 480), std::string const& windowName = "OpenCGE");
    void entityAdd(size_t entityId);
    void entityRemove(size_t entityId);
    void sceneLoad(const std::filesystem::path &filePath);
    void scenesLoad(const std::filesystem::path &directoryPath);
    void sceneUpdate(const nlohmann::json &message);
    void shutdown(const nlohmann::json &message);
    void update(const nlohmann::json &message);
    void windowResize(int width, int height);

  private:
    std::unordered_map<size_t, Component::Graphics3D *> components;
    GLFWwindow *window;
    std::unordered_map<std::string, Field::Scene3D> sceneTemplates;
  };
}

#endif
