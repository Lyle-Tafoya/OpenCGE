#include <OpenCGE/system.hpp>
#include <OpenCGE/graphics_ncurses.hpp>
#include <OpenCGE/physics.hpp>

int main()
{
  // Instantiate our systems
  OpenCGE::System::entitiesLoad("data/entities");
  OpenCGE::Physics physics_system;
  OpenCGE::GraphicsNcurses graphics_system;

  // Create a new entity
  size_t entity_id = OpenCGE::System::entityCreate("object_ncurses");
  OpenCGE::System::callbackTrigger("scene_update", {{"entity_id",entity_id},{"text","Hello World"}});
  OpenCGE::System::callbackTrigger("position_update", {{"entity_id",entity_id},{"x",5.f},{"y",2.f},{"z",0.f}});
  OpenCGE::System::callbackTrigger("velocity_apply", {{"entity_id",entity_id},{"x",0.f},{"y",1.f},{"z",0.f}});

  OpenCGE::System::timerStart();
  while(true)
  {
    OpenCGE::System::callbackTrigger("time_passed", {{"time_delta",OpenCGE::System::getTimeDelta()}});
  }

  OpenCGE::System::callbackTrigger("shutdown", {});
}
