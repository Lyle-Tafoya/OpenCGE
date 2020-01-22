#ifndef OPENCGE_GLFW_INPUT_HPP_
#define OPENCGE_GLFW_INPUT_HPP_

#include <string>
#include <vector>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>

#include <OpenCGE/system.hpp>

namespace OpenCGE
{
  class GLFWInput : public System
  {
  public:
    GLFWInput();

    void bindKeyToPlayer(int key, size_t playerId, const std::string &action);
    void bindFunctionToAction(std::function<void(size_t)> func, const std::string &action);
    void bindEntityToPlayer(size_t entityId, size_t playerId);

  private:
    struct Action
    {
      size_t entityId;
      std::function<void(size_t)> func;
      void operator()();
    };

    void entityAdd(size_t entityId) {};
    void entityRemove(size_t entityId) {};
    void update(const nlohmann::json &message);

    GLFWwindow *window;
    std::vector<std::unordered_map<int, std::string>> playerKeyToAction;
    std::unordered_map<std::string, std::function<void(size_t)>> actionToFunction;
    std::unordered_map<int, Action> keyboardActions;

    static void glfwCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
  };
}

#endif
