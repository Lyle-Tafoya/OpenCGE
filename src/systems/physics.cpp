#include <OpenCGE/physics.hpp>

namespace OpenCGE
{

  Physics::Physics()
  {
    componentsRegister({"orientation", "position", "torque", "velocity"});
    callbackRegister("position_update", &Physics::positionUpdate, this);
    callbackRegister("torque_apply", &Physics::torqueApply, this);
    callbackRegister("time_passed", &Physics::update, this);
    callbackRegister("velocity_apply", &Physics::velocityApply, this);
  }

  void Physics::positionUpdate(untyped_map & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    untyped_map &position = *(untyped_map *)entities[entity_id]["position"];

    *(float *)position["x"] = *(float *)message["x"];
    *(float *)position["y"] = *(float *)message["y"];
    *(float *)position["z"] = *(float *)message["z"];
  }

  void Physics::torqueApply(untyped_map & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    untyped_map &torque = *(untyped_map *)entities[entity_id]["torque"];

    *(float *)torque["pitch"] += *(float *)message["x"];
    *(float *)torque["roll"] += *(float *)message["y"];
    *(float *)torque["yaw"] += *(float *)message["z"];
  }

  void Physics::update(untyped_map & message)
  {
    float &time_delta = *(float *)message["time_delta"];
    for(auto entity : entities)
    {
      std::unordered_map<std::string,untyped_map *> &components = entity.second;

      untyped_map &position = *(untyped_map *)components["position"];
      untyped_map &velocity = *(untyped_map *)components["velocity"];
      *(float *)position["x"] += *(float *)velocity["x"] * time_delta;
      *(float *)position["y"] += *(float *)velocity["y"] * time_delta;
      *(float *)position["z"] += *(float *)velocity["z"] * time_delta;

      untyped_map &orientation = *(untyped_map *)components["orientation"];
      untyped_map &torque = *(untyped_map *)components["torque"];
      *(float *)orientation["pitch"] += *(float *)torque["pitch"] * time_delta;
      *(float *)orientation["roll"] += *(float *)torque["roll"] * time_delta;
      *(float *)orientation["yaw"] += *(float *)torque["yaw"] * time_delta;
    }
  }

  void Physics::velocityApply(untyped_map & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    untyped_map &velocity = *(untyped_map *)entities[entity_id]["velocity"];

    *(float *)velocity["x"] += *(float *)message["x"];
    *(float *)velocity["y"] += *(float *)message["y"];
    *(float *)velocity["z"] += *(float *)message["z"];
  }
}
