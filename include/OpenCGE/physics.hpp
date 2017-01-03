#ifndef _PHYSICS_HPP
#define _PHYSICS_HPP

#include <OpenCGE/system.hpp>

namespace OpenCGE
{
  class Physics : public System
  {
  public:
    Physics();
    void positionUpdate(Json & message);
    void torqueApply(Json & message);
    void update(Json & message);
    void velocityApply(Json & message);
  };
}

#endif
