#include <unistd.h>
#include "../../engine/system.hpp"
#include "../../systems/graphics_ncurses.hpp"
using namespace OpenCGE;

int main()
{
  System::componentsLoad("data/components");
  System::entitiesLoad("data/entities");

  GraphicsNcurses *graphics_system = new GraphicsNcurses();

  size_t entity_id = System::entityCreate("object_ncurses");
  json update_sprite;
  update_sprite["type_id"] = "scene_update"; update_sprite["entity_id"] = entity_id; update_sprite["string"] = "Hello World";
  System::callbackTrigger(update_sprite);

  json update_time;
  update_time["type_id"] = "time_passed"; update_time["time_delta"] = 0;
  System::callbackTrigger(update_time);
  
  sleep(2);;

  json shutdown;
  shutdown["type_id"] = "shutdown";
  System::callbackTrigger(shutdown);
}
