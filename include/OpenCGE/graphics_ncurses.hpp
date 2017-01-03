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
    void sceneUpdate(Json & message);
    void update(Json & message);
    void shutdown(Json & message);
  private:
    WINDOW *screen;
  };
}

#endif
