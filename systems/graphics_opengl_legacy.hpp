#include "../engine/system.hpp"
#include <GLFW/glfw3.h>
#include <unordered_map>
  using std::unordered_map;

namespace OpenCGE
{
  class GraphicsOpenGLLegacy : public System
  {
  public:
    GraphicsOpenGLLegacy();
    void modelLoad(string const& file_path);
    void modelsLoad(string const& directory_path);
    void sceneUpdate(json const& message);
    void shutdown(json const& message);
    void update(json const& message);
    void windowResize(int width, int height);
  private:
    GLFWwindow *window;
    unordered_map<string,json> model_registry;
  };
}
