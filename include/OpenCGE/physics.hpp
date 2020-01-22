#ifndef OPENCGE_PHYSICS_HPP_
#define OPENCGE_PHYSICS_HPP_

#include <nlohmann/json.hpp>

#include <OpenCGE/system.hpp>
#include <OpenCGE/components/physics.hpp>

namespace OpenCGE
{
  class Physics : public System
  {
  public:
    Physics();
    void entityAdd(size_t entityId);
    void entityRemove(size_t entityId);
    void positionUpdate(const nlohmann::json &message);
    void torqueApply(const nlohmann::json &message);
    void update(const nlohmann::json &message);
    void velocityApply(const nlohmann::json &message);

  private:
    std::unordered_map<size_t, Component::Physics *> components;
  };
}

#endif
