#ifndef OPENCGE_COMPONENT_GRAPHICS_3D_HPP_
#define OPENCGE_COMPONENT_GRAPHICS_3D_HPP_

#include <glm/glm.hpp>

#include <OpenCGE/fields/scene_3d.hpp>

namespace OpenCGE::Component
{
  struct Graphics3D
  {
    glm::vec3 &orientation;
    glm::vec3 &position;
    Field::Scene3D &scene;
  };
}

#endif
