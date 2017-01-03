#include <OpenCGE/system.hpp>
#include <OpenCGE/physics.hpp>
#include <OpenCGE/graphics_ncurses.hpp>

int main()
{
  // Load components and entities
  OpenCGE::System::componentsLoad("data/components");
  OpenCGE::System::entitiesLoad("data/entities");

  // Instantiate our systems
  OpenCGE::GraphicsNcurses graphics_system;
  OpenCGE::Physics physics_system;

  // Create a new entity
  size_t entity_id = OpenCGE::System::entityCreate("object_ncurses");
  OpenCGE::System::callbackTrigger({{"type_id","scene_update"},{"entity_id",entity_id},{"string","Hello World"}});
  OpenCGE::System::callbackTrigger({{"type_id","position_update"},{"entity_id",entity_id},{"x",5},{"y",2},{"z",0}});
  OpenCGE::System::callbackTrigger({{"type_id","velocity_apply"},{"entity_id",entity_id},{"x",0},{"y",1},{"z",0}});

  OpenCGE::System::timerStart();
  while(true)
  {
    OpenCGE::System::callbackTrigger({{"type_id","time_passed"},{"time_delta",OpenCGE::System::getTimeDelta()}});
  }

  OpenCGE::System::callbackTrigger({{"type_id","shutdown"}});
}
