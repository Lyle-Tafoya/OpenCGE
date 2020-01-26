#include <OpenCGE/system.hpp>
#include <OpenCGE/glfw_input.hpp>
#include <OpenCGE/graphics_opengl_legacy.hpp>
#include <OpenCGE/physics.hpp>

bool running = true;
void shutdown(size_t) { running = false; }

int main()
{
  OpenCGE::Physics physics_system;
  OpenCGE::GraphicsOpenGLLegacy graphics_system;
  OpenCGE::GLFWInput input_system;

  OpenCGE::System::entitiesLoad("data/entities");
  graphics_system.sceneLoad("assets/models/hello_world.dae");

  input_system.bindFunctionToAction(shutdown, "shutdown");
  input_system.bindKeyToPlayer(GLFW_KEY_ESCAPE, 1, "shutdown");
  input_system.bindEntityToPlayer(0, 1);

  size_t entityId = OpenCGE::System::entityCreate("data/entities/object_3d");
  OpenCGE::System::callbackTrigger("scene_update",{{"entity_id",entityId},{"scene_name","assets/models/hello_world.dae"}});
  OpenCGE::System::callbackTrigger("torque_apply",{{"entity_id",entityId},{"x",10},{"y",10},{"z",10}});

  OpenCGE::System::timerStart();
  while(running)
  {
    OpenCGE::System::callbackTrigger("time_passed", {{"time_delta",OpenCGE::System::getTimeDelta()}});
  }
  OpenCGE::System::callbackTrigger("shutdown", {});
}
