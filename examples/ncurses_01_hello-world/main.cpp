#include <unistd.h>
#include <chrono>
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;
  using std::chrono::time_point;
#include "../../engine/system.hpp"
#include "../../systems/graphics_ncurses.hpp"
#include "../../systems/physics.hpp"
  using namespace OpenCGE;

int main()
{
  // Load components and entities
  System::componentsLoad("data/components");
  System::entitiesLoad("data/entities");

  // Instantiate our systems
  GraphicsNcurses graphics_system;
  Physics physics_system;

  // Create a new entity
  size_t entity_id = System::entityCreate("object_ncurses");
  System::callbackTrigger({{"type_id","scene_update"},{"entity_id",entity_id},{"string","Hello World"}});
  System::callbackTrigger({{"type_id","position_update"},{"entity_id",entity_id},{"x",5},{"y",2},{"z",0}});
  System::callbackTrigger({{"type_id","velocity_apply"},{"entity_id",entity_id},{"x",0},{"y",1},{"z",0}});

  high_resolution_clock timer;
  auto program_start = timer.now();
  auto current_time = program_start, previous_time = program_start;
  float delta_time = 0.f;

  while(true)
  {
    previous_time = current_time;
    current_time = timer.now();
    delta_time = duration_cast<milliseconds>(current_time - previous_time).count() / 1000.f;
    System::callbackTrigger({{"type_id","time_passed"},{"time_delta",delta_time}});
    sleep(1);
  }

  System::callbackTrigger({{"type_id","shutdown"}});
}
