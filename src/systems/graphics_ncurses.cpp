#include <OpenCGE/graphics_ncurses.hpp>

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
    json &scene_component = *entities[message["entity_id"].get<size_t>()]["scene_ncurses"];
    scene_component["string"] = message["string"];
  }

  void GraphicsNcurses::update(json const& message)
  {
    for(auto entity : entities)
    {
      unordered_map<string,json *> components = entity.second;
      json &position = *components["position"];
      json &scene = *components["scene_ncurses"];
      mvwaddstr(screen, position["y"], position["x"], scene["string"].get<string>().c_str());
    }
    wrefresh(screen);
    for(auto entity : entities)
    {
      unordered_map<string,json *> components = entity.second;
      json &position = *components["position"];
      json &scene = *components["scene_ncurses"];

      mvwaddstr(screen, position["y"], position["x"], string(scene["string"].get<string>().size(),' ').c_str());
    }
  }

  void GraphicsNcurses::shutdown(json const& message)
  {
    endwin();
  }
}
