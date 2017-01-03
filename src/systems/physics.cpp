#include <OpenCGE/physics.hpp>

namespace OpenCGE
{

  Physics::Physics()
  {
    componentsRegister({"orientation", "position", "torque", "velocity"});

    System::callbackRegister("position_update", &Physics::positionUpdate, this);
    System::callbackRegister("torque_apply", &Physics::torqueApply, this);
    System::callbackRegister("time_passed", &Physics::update, this);
    System::callbackRegister("velocity_apply", &Physics::velocityApply, this);
  }

  void Physics::positionUpdate(Json & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    Json &position = *(Json *)entities[entity_id]["position"];

    *(float *)position["x"] = *(float *)message["x"];
    *(float *)position["y"] = *(float *)message["y"];
    *(float *)position["z"] = *(float *)message["z"];
  }

  void Physics::torqueApply(Json & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    Json &torque = *(Json *)entities[entity_id]["torque"];

    *(float *)torque["pitch"] += *(float *)message["x"];
    *(float *)torque["roll"] += *(float *)message["y"];
    *(float *)torque["yaw"] += *(float *)message["z"];
  }

  void Physics::update(Json & message)
  {
    float &time_delta = *(float *)message["time_delta"];
    for(auto entity : entities)
    {
      std::unordered_map<std::string,Json *> &components = entity.second;

      Json &position = *(Json *)components["position"];
      Json &velocity = *(Json *)components["velocity"];
      *(float *)position["x"] += *(float *)velocity["x"] * time_delta;
      *(float *)position["y"] += *(float *)velocity["y"] * time_delta;
      *(float *)position["z"] += *(float *)velocity["z"] * time_delta;

      Json &orientation = *(Json *)components["orientation"];
      Json &torque = *(Json *)components["torque"];
      *(float *)orientation["pitch"] += *(float *)torque["pitch"] * time_delta;
      *(float *)orientation["roll"] += *(float *)torque["roll"] * time_delta;
      *(float *)orientation["yaw"] += *(float *)torque["yaw"] * time_delta;
    }
  }

  void Physics::velocityApply(Json & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    Json &velocity = *(Json *)entities[entity_id]["velocity"];

    *(float *)velocity["x"] += *(float *)message["x"];
    *(float *)velocity["y"] += *(float *)message["y"];
    *(float *)velocity["z"] += *(float *)message["z"];
  }
}
