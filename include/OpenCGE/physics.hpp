#ifndef _PHYSICS_HPP
#define _PHYSICS_HPP

#include <OpenCGE/system.hpp>

namespace OpenCGE
{
  class Physics : public System
  {
  public:
    Physics();
    void positionUpdate(untyped_map & message);
    void torqueApply(untyped_map & message);
    void update(untyped_map & message);
    void velocityApply(untyped_map & message);
  };
}

#endif
