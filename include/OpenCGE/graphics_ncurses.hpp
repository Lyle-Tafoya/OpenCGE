#include <OpenCGE/system.hpp>
#include <ncurses.h>

namespace OpenCGE
{
  class GraphicsNcurses : public System
  {
  public:
    GraphicsNcurses();
    void sceneUpdate(json const& message);
    void update(json const& message);
    void shutdown(json const& message);
  private:
    WINDOW *screen;
  };
}
