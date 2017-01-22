#ifndef INCLUDE_OPENCGE_COMPONENTS_GRAPHICS_3D_HPP_
#define INCLUDE_OPENCGE_COMPONENTS_GRAPHICS_3D_HPP_

#include <OpenCGE/fields/point_3d.hpp>
#include <OpenCGE/fields/scene_3d.hpp>

namespace OpenCGE
{
  namespace Component
  {
    struct Graphics3D
    {
      Field::Point3D &orientation;
      Field::Point3D &position;
      Field::Scene3D &scene;

      Graphics3D(Field::Point3D &orientation, Field::Point3D &position, Field::Scene3D &scene)
        : orientation(orientation), position(position), scene(scene) {}
    };
  }
}

#endif /* INCLUDE_OPENCGE_COMPONENTS_GRAPHICS_3D_HPP_ */
