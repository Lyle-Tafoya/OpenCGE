#ifndef _GRAPHICS_NCURSES_HPP
#define _GRAPHICS_NCURSES_HPP

#include <OpenCGE/system.hpp>
#include <ncurses.h>

namespace OpenCGE
{
  class GraphicsNcurses : public System
  {
  public:
    GraphicsNcurses();
    void sceneUpdate(untyped_map & message);
    void update(untyped_map & message);
    void shutdown(untyped_map & message);
  private:
    WINDOW *screen;
  };
}

#endif
