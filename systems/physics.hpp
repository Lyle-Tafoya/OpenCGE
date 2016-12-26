#include "../engine/system.hpp"

namespace OpenCGE
{
  class Physics : public System
  {
  public:
    Physics();
    void positionUpdate(json const& message);
    void torqueApply(json const& message);
    void update(json const& message);
    void velocityApply(json const& message);
  };
}
