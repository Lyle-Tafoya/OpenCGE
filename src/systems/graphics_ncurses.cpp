#include <OpenCGE/graphics_ncurses.hpp>

namespace OpenCGE
{

  GraphicsNcurses::GraphicsNcurses()
  {
    componentRegister("position", &createPoint3D);
    componentRegister("scene_ncurses", &createSceneNcurses);
    callbackRegister("shutdown", &GraphicsNcurses::shutdown, this);
    callbackRegister("scene_update", &GraphicsNcurses::sceneUpdate, this);
    callbackRegister("time_passed", &GraphicsNcurses::update, this);
    screen = initscr();
    curs_set(0);
  }

  void * GraphicsNcurses::createPoint3D()
  {
    return new Components::Point3D();
  }

  void * GraphicsNcurses::createSceneNcurses()
  {
    return new Components::SceneNcurses();
  }

  void GraphicsNcurses::sceneUpdate(untyped_map & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    auto &scene_ncurses = *(Components::SceneNcurses *)entities[entity_id]["scene_ncurses"];
    scene_ncurses.text = *(std::string *)message["text"];
  }

  void GraphicsNcurses::update(untyped_map &)
  {
    for(auto entity : entities)
    {
      untyped_map &components = entity.second;
      auto &position = *(Components::Point3D *)components["position"];
      auto &scene_ncurses = *(Components::SceneNcurses *)components["scene_ncurses"];
      mvwaddstr(screen, (int)position.y, (int)position.x, scene_ncurses.text.c_str());
    }
    wrefresh(screen);
    for(auto entity : entities)
    {
      untyped_map &components = entity.second;
      auto &position = *(Components::Point3D *)components["position"];
      auto &scene_ncurses = *(Components::SceneNcurses *)components["scene_ncurses"];
      std::string empty_str(scene_ncurses.text.size(), ' ');
      mvwaddstr(screen, (int)position.y, (int)position.x, empty_str.c_str());
    }
  }

  void GraphicsNcurses::shutdown(untyped_map &)
  {
    endwin();
  }
}
