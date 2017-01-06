#ifndef _GRAPHICS_NCURSES_HPP
#define _GRAPHICS_NCURSES_HPP

#include <OpenCGE/system.hpp>
#include <OpenCGE/components/point_3d.hpp>
#include <OpenCGE/components/scene_ncurses.hpp>
#include <ncurses.h>

namespace OpenCGE
{
  class GraphicsNcurses : public System
  {
  public:
    GraphicsNcurses();
    static void * createPoint3D();
    static void * createSceneNcurses();
    void sceneUpdate(nlohmann::json const& message);
    void update(nlohmann::json const& message);
    void shutdown(nlohmann::json const& message);
  private:
    WINDOW *screen;
  };
}

#endif
