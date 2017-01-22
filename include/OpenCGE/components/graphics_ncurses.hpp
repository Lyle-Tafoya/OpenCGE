#ifndef INCLUDE_OPENCGE_COMPONENTS_GRAPHICS_NCURSES_HPP_
#define INCLUDE_OPENCGE_COMPONENTS_GRAPHICS_NCURSES_HPP_

#include <OpenCGE/fields/point_3d.hpp>
#include <OpenCGE/fields/scene_ncurses.hpp>

namespace OpenCGE
{
  namespace Component
  {
    struct GraphicsNcurses
    {
      Field::Point3D &orientation;
      Field::Point3D &position;
      Field::SceneNcurses &scene;

      GraphicsNcurses(Field::Point3D &orientation, Field::Point3D &position, Field::SceneNcurses &scene)
        : orientation(orientation), position(position), scene(scene) {}
    };
  }
}

#endif /* INCLUDE_OPENCGE_COMPONENTS_GRAPHICS_NCURSES_HPP_ */
