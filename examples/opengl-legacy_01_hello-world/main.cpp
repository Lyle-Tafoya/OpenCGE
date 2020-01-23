#include <OpenCGE/system.hpp>
#include <OpenCGE/glfw_input.hpp>
#include <OpenCGE/graphics_opengl_legacy.hpp>
#include <OpenCGE/physics.hpp>

bool running = true;
void shutdown(size_t entityId) { running = false; }

int randNum(int from, int to) { return (rand() % (to-from+1)) + from; }

int main()
{
  OpenCGE::System::entitiesLoad("data/entities");
  OpenCGE::Physics physics_system;
  OpenCGE::GraphicsOpenGLLegacy graphics_system;
  graphics_system.scenesLoad("assets/models");
  OpenCGE::GLFWInput input_system;

  input_system.bindFunctionToAction(shutdown, "shutdown");
  input_system.bindKeyToPlayer(GLFW_KEY_ESCAPE, 1, "shutdown");
  input_system.bindEntityToPlayer(0, 1);

  size_t entityId = OpenCGE::System::entityCreate("data/entities/object_3d");
  OpenCGE::System::callbackTrigger("scene_update", {{"entity_id",entityId},{"scene_name","assets/models/hello_world.dae"}});
  OpenCGE::System::callbackTrigger("torque_apply", {{"entity_id",entityId},{"x",20.f},{"y",20.f},{"z",0.f}});

  for(size_t i = 0; i < 200; ++i)
  {
    entityId = OpenCGE::System::entityCreate("data/entities/object_3d");
    OpenCGE::System::callbackTrigger("scene_update", {{"entity_id",entityId},{"scene_name","assets/models/hello_world.dae"}});
    OpenCGE::System::callbackTrigger("velocity_apply", {{"entity_id",entityId},{"x",0.f},{"y",0.f},{"z",-0.2f}});
    OpenCGE::System::callbackTrigger("torque_apply", {
        {"entity_id", entityId},
        {"x", randNum(0, 20)},{
        "y", randNum(0,20)},
        {"z", randNum(0,20)}
    });
  }

  OpenCGE::System::timerStart();
  while(running)
  {
    OpenCGE::System::callbackTrigger("time_passed", {{"time_delta",OpenCGE::System::getTimeDelta()}});
  }
  OpenCGE::System::callbackTrigger("shutdown", {});
}
