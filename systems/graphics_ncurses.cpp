#include "graphics_ncurses.hpp"

namespace OpenCGE
{

  GraphicsNcurses::GraphicsNcurses()
  {
    componentsRegister({"position", "scene_ncurses"});
    System::callbackRegister("shutdown", &GraphicsNcurses::shutdown, this);
    System::callbackRegister("scene_update", &GraphicsNcurses::sceneUpdate, this);
    System::callbackRegister("time_passed", &GraphicsNcurses::update, this);
    screen = initscr();
    curs_set(0);
  }

  void GraphicsNcurses::sceneUpdate(json const& message)
  {
    entities[message["entity_id"]]["scene_ncurses"]["string"] = message["string"];
  }

  void GraphicsNcurses::update(json const& message)
  {
    for(auto entity : entities)
    {
      size_t entity_id = entity.first;
      json components = entity.second;
      json position = components["position"];
      mvwaddstr(screen, position["y"], position["x"], components["scene_ncurses"]["string"].get<string>().c_str());
      wrefresh(screen);
    }
  }

  void GraphicsNcurses::shutdown(json const& message)
  {
    endwin();
  }
}
