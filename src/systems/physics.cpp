#include <OpenCGE/physics.hpp>

namespace OpenCGE
{

  Physics::Physics()
  {
    componentRegister("orientation", &createPoint3D);
    componentRegister("position", &createPoint3D);
    componentRegister("torque", &createPoint3D);
    componentRegister("velocity", &createPoint3D);
    callbackRegister("position_update", &Physics::positionUpdate, this);
    callbackRegister("torque_apply", &Physics::torqueApply, this);
    callbackRegister("time_passed", &Physics::update, this);
    callbackRegister("velocity_apply", &Physics::velocityApply, this);
  }

  void * Physics::createPoint3D()
  {
    return new Components::Point3D();
  }

  void Physics::positionUpdate(nlohmann::json const& message)
  {
    size_t entity_id = message["entity_id"];
    auto &position = *(Components::Point3D *)entities[entity_id]["position"];

    position.x = message["x"];
    position.y = message["y"];
    position.z = message["z"];
  }

  void Physics::torqueApply(nlohmann::json const& message)
  {
    size_t entity_id = message["entity_id"];
    auto &torque = *(Components::Point3D *)entities[entity_id]["torque"];

    torque.x += message["x"].get<float>();
    torque.y += message["y"].get<float>();
    torque.z += message["z"].get<float>();
  }

  void Physics::update(nlohmann::json const& message)
  {
    float time_delta = message["time_delta"];
    for(auto entity : entities)
    {
      untyped_map &components = entity.second;

      auto &position = *(Components::Point3D *)components["position"];
      auto &velocity = *(Components::Point3D *)components["velocity"];
      position.x += velocity.x * time_delta;
      position.y += velocity.y * time_delta;
      position.z += velocity.z * time_delta;

      auto &orientation = *(Components::Point3D *)components["orientation"];
      auto &torque = *(Components::Point3D *)components["torque"];
      orientation.x += torque.x * time_delta;
      orientation.y += torque.y * time_delta;
      orientation.z += torque.z * time_delta;
    }
  }

  void Physics::velocityApply(nlohmann::json const& message)
  {
    size_t entity_id = message["entity_id"];
    auto &velocity = *(Components::Point3D *)entities[entity_id]["velocity"];

    velocity.x += message["x"].get<float>();
    velocity.y += message["y"].get<float>();
    velocity.z += message["z"].get<float>();
  }
}
