#ifndef OPENCGE_COMPONENTS_PHYSICS_HPP_
#define OPENCGE_COMPONENTS_PHYSICS_HPP_

#include <OpenCGE/fields/point_3d.hpp>

namespace OpenCGE
{
  namespace Component
  {
    struct Physics
    {

      Field::Point3D &orientation;
      Field::Point3D &position;
      Field::Point3D &torque;
      Field::Point3D &velocity;

      Physics(Field::Point3D &orientation, Field::Point3D &position, Field::Point3D &torque, Field::Point3D &velocity)
        : orientation(orientation), position(position), torque(torque), velocity(velocity) {};
    };
  }
}


#endif
