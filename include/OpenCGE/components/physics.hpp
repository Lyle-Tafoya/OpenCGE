#ifndef OPENCGE_COMPONENTS_PHYSICS_HPP_
#define OPENCGE_COMPONENTS_PHYSICS_HPP_

#include <glm/glm.hpp>

namespace OpenCGE::Component
{
  struct Physics
  {

    glm::vec3 &orientation;
    glm::vec3 &position;
    glm::vec3 &torque;
    glm::vec3 &velocity;

    Physics(glm::vec3 &orientation, glm::vec3 &position, glm::vec3 &torque, glm::vec3 &velocity)
      : orientation(orientation), position(position), torque(torque), velocity(velocity) {};
  };
}


#endif
