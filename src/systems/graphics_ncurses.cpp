#include <OpenCGE/graphics_ncurses.hpp>

namespace OpenCGE
{

  GraphicsNcurses::GraphicsNcurses()
    : System("graphics_ncurses")
  {
    callbackRegister("shutdown", &GraphicsNcurses::shutdown, this);
    callbackRegister("scene_update", &GraphicsNcurses::sceneUpdate, this);
    callbackRegister("time_passed", &GraphicsNcurses::update, this);
    screen = initscr();
    curs_set(0);
  }

  void GraphicsNcurses::entityAdd(size_t entity_id)
  {
    std::unordered_map<std::string, void *> &entity = entities[entity_id];

    auto *orientation = (Field::Point3D *)entity["orientation"];
    if(orientation == nullptr)
    {
      orientation = new Field::Point3D(0.f, 0.f, 0.f);
      entity["orientation"] = orientation;
    }
    auto *position = (Field::Point3D *)entity["position"];
    if(position == nullptr)
    {
      position = new Field::Point3D(0.f, 0.f, 0.f);
      entity["position"] = position;
    }
    auto *scene = (Field::SceneNcurses *)entity["scene_ncurses"];
    if(scene == nullptr)
    {
      scene = new Field::SceneNcurses("@");
      entity["scene_ncurses"] = scene;
    }

    components[entity_id] = new Component::GraphicsNcurses(*orientation, *position, *scene);
  }

  void GraphicsNcurses::entityRemove(size_t entity_id)
  {
    delete components[entity_id];
    components.erase(entity_id);
  }

  void GraphicsNcurses::sceneUpdate(nlohmann::json const& message)
  {
    size_t entity_id = message["entity_id"];
    Field::SceneNcurses &scene = components[entity_id]->scene;
    scene.text = message["text"].get<std::string>();
  }

  void GraphicsNcurses::update(nlohmann::json const&)
  {
    for(auto entity : components)
    {
      Component::GraphicsNcurses &component = *entity.second;
      mvwaddstr(screen, (int)component.position.y, (int)component.position.x, component.scene.text.c_str());
    }
    wrefresh(screen);
    for(auto entity : components)
    {
      Component::GraphicsNcurses &component = *entity.second;
      std::string empty_str(component.scene.text.size(), ' ');
      mvwaddstr(screen, (int)component.position.y, (int)component.position.x, empty_str.c_str());
    }
  }

  void GraphicsNcurses::shutdown(nlohmann::json const&)
  {
    endwin();
  }
}
