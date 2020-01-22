#include <OpenCGE/system.hpp>
#include <OpenCGE/glfw_input.hpp>
#include <OpenCGE/graphics_opengl_legacy.hpp>
#include <OpenCGE/physics.hpp>

void resetEntityPosition(size_t entityId)
{
  OpenCGE::System::callbackTrigger("position_update",{{"entity_id", entityId}, {"x", 0.f}, {"y", 0.f}, {"z", 0.f}});
}

bool running = true;
void shutdown(size_t entityId)
{
  running = false;
}

int main()
{
  OpenCGE::System::entitiesLoad("data/entities");
  OpenCGE::Physics physics_system;

  OpenCGE::GLFWInput input_system;
  input_system.bindFunctionToAction(shutdown, "shutdown");
  input_system.bindKeyToPlayer(GLFW_KEY_Q, 1, "shutdown");
  input_system.bindFunctionToAction(resetEntityPosition, "reset");
  input_system.bindKeyToPlayer(GLFW_KEY_SPACE, 1, "reset");

  OpenCGE::GraphicsOpenGLLegacy graphics_system;
  graphics_system.scenesLoad("assets/models");

  size_t entityId = OpenCGE::System::entityCreate("data/entities/object_3d");
  input_system.bindEntityToPlayer(entityId, 1);
  OpenCGE::System::callbackTrigger("scene_update", {{"entity_id",entityId},{"scene_name","assets/models/hello_world.dae"}});
  OpenCGE::System::callbackTrigger("torque_apply", {{"entity_id",entityId},{"x",20.f},{"y",20.f},{"z",0.f}});
  OpenCGE::System::callbackTrigger("velocity_apply", {{"entity_id",entityId},{"x",0.f},{"y",0.f},{"z",-1.f}});

  OpenCGE::System::timerStart();
  while(running)
  {
    OpenCGE::System::callbackTrigger("time_passed", {{"time_delta",OpenCGE::System::getTimeDelta()}});
  }
  OpenCGE::System::callbackTrigger("shutdown", {});
}
