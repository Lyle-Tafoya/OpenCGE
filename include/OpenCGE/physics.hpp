#ifndef _PHYSICS_HPP
#define _PHYSICS_HPP

#include <OpenCGE/system.hpp>
#include <OpenCGE/components/physics.hpp>

namespace OpenCGE
{
  class Physics : public System
  {
  public:
    Physics();
    void entityAdd(size_t entity_id);
    void entityRemove(size_t entity_id);
    void positionUpdate(nlohmann::json const& message);
    void torqueApply(nlohmann::json const& message);
    void update(nlohmann::json const& message);
    void velocityApply(nlohmann::json const& message);

  private:
    std::unordered_map<size_t,Component::Physics *> components;
  };
}

#endif
