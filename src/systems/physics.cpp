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

  void Physics::positionUpdate(untyped_map & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    auto &position = *(Components::Point3D *)entities[entity_id]["position"];

    position.x = *(float *)message["x"];
    position.y = *(float *)message["y"];
    position.z = *(float *)message["z"];
  }

  void Physics::torqueApply(untyped_map & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    auto &torque = *(Components::Point3D *)entities[entity_id]["torque"];

    torque.x += *(float *)message["x"];
    torque.y += *(float *)message["y"];
    torque.z += *(float *)message["z"];
  }

  void Physics::update(untyped_map & message)
  {
    float &time_delta = *(float *)message["time_delta"];
    for(auto entity : entities)
    {
      std::unordered_map<std::string,void *> &components = entity.second;

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

  void Physics::velocityApply(untyped_map & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    auto &velocity = *(Components::Point3D *)entities[entity_id]["velocity"];

    velocity.x += *(float *)message["x"];
    velocity.y += *(float *)message["y"];
    velocity.z += *(float *)message["z"];
  }
}
