#include <OpenCGE/system.hpp>
#include <OpenCGE/graphics_opengl_legacy.hpp>
#include <OpenCGE/physics.hpp>

int main()
{
  // Load components and entities
  OpenCGE::System::componentsLoad("data/components");
  OpenCGE::System::entitiesLoad("data/entities");

  // Instantiate our systems
  OpenCGE::Physics physics_system;
  OpenCGE::GraphicsOpenGLLegacy graphics_system;
  graphics_system.scenesLoad("assets/models");

  // Create a new entity
  size_t entity_id = OpenCGE::System::entityCreate("object_3d");
  OpenCGE::System::callbackTrigger({{"type_id","scene_update"},{"entity_id",entity_id},{"scene_name","hello_world"}});
  OpenCGE::System::callbackTrigger({{"type_id","torque_apply"},{"entity_id",entity_id},{"x",50.f},{"y",50.f},{"z",0.f}});
  OpenCGE::System::callbackTrigger({{"type_id","velocity_apply"},{"entity_id",entity_id},{"x",0.f},{"y",0.f},{"z",-0.1f}});

  OpenCGE::System::timerStart();
  while(true)
  {
    OpenCGE::System::callbackTrigger({{"type_id","time_passed"},{"time_delta",OpenCGE::System::getTimeDelta()}});
  }

  OpenCGE::System::callbackTrigger({{"type_id","shutdown"}});
}
