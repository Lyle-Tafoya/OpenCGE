#include <OpenCGE/graphics_ncurses.hpp>

namespace OpenCGE
{

  GraphicsNcurses::GraphicsNcurses()
  {
    componentsRegister({"position", "scene_ncurses"});
    callbackRegister("shutdown", &GraphicsNcurses::shutdown, this);
    callbackRegister("scene_update", &GraphicsNcurses::sceneUpdate, this);
    callbackRegister("time_passed", &GraphicsNcurses::update, this);
    screen = initscr();
    curs_set(0);
  }

  void GraphicsNcurses::sceneUpdate(untyped_map & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    untyped_map &scene_ncurses = *(untyped_map *)entities[entity_id]["scene_ncurses"];
    *(std::string *)scene_ncurses["string"] = *(std::string *)message["string"];
  }

  void GraphicsNcurses::update(untyped_map &)
  {
    for(auto entity : entities)
    {
      std::unordered_map<std::string, untyped_map *> &components = entity.second;
      untyped_map &position = *components["position"];
      untyped_map &scene_ncurses = *components["scene_ncurses"];
      mvwaddstr(screen, (int)*(float *)position["y"], (int)*(float *)position["x"], ((std::string *)scene_ncurses["string"])->c_str());
    }
    wrefresh(screen);
    for(auto entity : entities)
    {
      std::unordered_map<std::string, untyped_map *> &components = entity.second;
      untyped_map &position = *components["position"];
      untyped_map &scene_ncurses = *components["scene_ncurses"];
      std::string empty_str(((std::string *)scene_ncurses["string"])->size(), ' ');
      mvwaddstr(screen, (int)*(float *)position["y"], (int)*(float *)position["x"], empty_str.c_str());
    }
  }

  void GraphicsNcurses::shutdown(untyped_map &)
  {
    endwin();
  }
}
