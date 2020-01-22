#include <unordered_map>

#include <nlohmann/json.hpp>

#include <OpenCGE/glfw_input.hpp>
#include <OpenCGE/glfw_singleton.hpp>

namespace OpenCGE
{
  void GLFWInput::Action::operator()() { func(entityId); }

  void GLFWInput::bindKeyToPlayer(int key, size_t playerId, const std::string &action)
  {
    if(playerKeyToAction.size() < playerId) { playerKeyToAction.resize(playerId); }
    playerKeyToAction[playerId-1][key] = action;
  }

  void GLFWInput::bindEntityToPlayer(size_t entityId, size_t playerId)
  {
    for(const auto &kv : playerKeyToAction[playerId-1])
    {
      keyboardActions[kv.first] = {entityId, actionToFunction[kv.second]};
    }
  }

  void GLFWInput::bindFunctionToAction(std::function<void(size_t)> func, const std::string &action)
  {
    actionToFunction[action] = func;
  }

  void GLFWInput::glfwCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
  {
    auto *inputSystem = static_cast<GLFWInput *>(glfwGetWindowUserPointer(window));
    auto keyboardAction = inputSystem->keyboardActions.find(key);
    if(keyboardAction == inputSystem->keyboardActions.end()) { return; }
    keyboardAction->second();
  }

  GLFWInput::GLFWInput() : System("input")
  {
    callbackRegister("time_passed", &GLFWInput::update, this);
    window = GLFWSingleton::get();
    glfwSetKeyCallback(window, glfwCallback);
    glfwSetWindowUserPointer(window, this);
  }

  void GLFWInput::update(const nlohmann::json &message)
  {
    glfwPollEvents();
  }
}
