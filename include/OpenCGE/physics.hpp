#ifndef _PHYSICS_HPP
#define _PHYSICS_HPP

#include <OpenCGE/system.hpp>
#include <OpenCGE/components/point_3d.hpp>

namespace OpenCGE
{
  class Physics : public System
  {
  public:
    Physics();
    static void * createPoint3D();
    void positionUpdate(nlohmann::json const& message);
    void torqueApply(nlohmann::json const& message);
    void update(nlohmann::json const& message);
    void velocityApply(nlohmann::json const& message);
  };
}

#endif
