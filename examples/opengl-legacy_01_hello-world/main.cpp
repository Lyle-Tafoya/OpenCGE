#include <OpenCGE/system.hpp>
#include <OpenCGE/graphics_opengl_legacy.hpp>
#include <OpenCGE/physics.hpp>

int main()
{
  // Instantiate our systems
  OpenCGE::System::entitiesLoad("data/entities");
  OpenCGE::Physics physics_system;
  OpenCGE::GraphicsOpenGLLegacy graphics_system;
  graphics_system.scenesLoad("assets/models");

  // Create a new entity
  size_t entity_id = OpenCGE::System::entityCreate("data/entities/object_3d");
  OpenCGE::System::callbackTrigger(
      "scene_update", {
        {"entity_id",entity_id},
        {"scene_name","assets/models/hello_world.dae"}
  });
  OpenCGE::System::callbackTrigger("torque_apply", {{"entity_id",entity_id},{"x",50.f},{"y",50.f},{"z",0.f}});
  OpenCGE::System::callbackTrigger("velocity_apply", {{"entity_id",entity_id},{"x",0.f},{"y",0.f},{"z",-0.1f}});

  OpenCGE::System::timerStart();
  while(true)
  {
    OpenCGE::System::callbackTrigger("time_passed", {{"time_delta",OpenCGE::System::getTimeDelta()}});
  }

  OpenCGE::System::callbackTrigger("shutdown", {});
}
