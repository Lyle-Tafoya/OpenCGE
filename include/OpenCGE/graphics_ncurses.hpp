#ifndef _GRAPHICS_NCURSES_HPP
#define _GRAPHICS_NCURSES_HPP

#include <OpenCGE/system.hpp>
#include <ncurses.h>
#include <OpenCGE/components/graphics_ncurses.hpp>

namespace OpenCGE
{
  class GraphicsNcurses : public System
  {
  public:
    GraphicsNcurses();
    void entityAdd(size_t entity_id);
    void entityRemove(size_t entity_id);
    static void * createPoint3D();
    static void * createSceneNcurses();
    void sceneUpdate(nlohmann::json const& message);
    void update(nlohmann::json const& message);
    void shutdown(nlohmann::json const& message);

  private:
    std::unordered_map<size_t,Component::GraphicsNcurses *> components;
    WINDOW *screen;
  };
}

#endif
