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

  void GraphicsNcurses::sceneUpdate(Json & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    Json &scene_ncurses = *(Json *)entities[entity_id]["scene_ncurses"];
    *(std::string *)scene_ncurses["string"] = *(std::string *)message["string"];
  }

  void GraphicsNcurses::update(Json & message)
  {
    for(auto entity : entities)
    {
      std::unordered_map<std::string, Json *> &components = entity.second;
      Json &position = *components["position"];
      Json &scene_ncurses = *components["scene_ncurses"];
      mvwaddstr(screen, *(int *)position["y"], *(int *)position["x"], ((std::string *)scene_ncurses["string"])->c_str());
    }
    wrefresh(screen);
    for(auto entity : entities)
    {
      std::unordered_map<std::string, Json *> &components = entity.second;
      Json &position = *components["position"];
      Json &scene_ncurses = *components["scene_ncurses"];
      std::string empty_str(((std::string *)scene_ncurses["string"])->size(), ' ');
      mvwaddstr(screen, *(int *)position["y"], *(int *)position["x"], empty_str.c_str());
    }
  }

  void GraphicsNcurses::shutdown(Json & message)
  {
    endwin();
  }
}
