#include <OpenCGE/physics.hpp>
#include <iostream>

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

  void Physics::positionUpdate(json const& message)
  {
    json &position = *entities[message["entity_id"]]["position"];
    position["x"] = message["x"];
    position["y"] = message["y"];
    position["z"] = message["z"];
  }

  void Physics::torqueApply(json const& message)
  {
    json &torque = *entities[message["entity_id"]]["torque"];
    torque["pitch"] = torque["pitch"].get<float>() + message["x"].get<float>();
    torque["roll"] = torque["roll"].get<float>() + message["y"].get<float>();
    torque["yaw"] = torque["yaw"].get<float>() + message["z"].get<float>();
  }

  void Physics::update(json const& message)
  {
    float time_delta = message["time_delta"];
    for(auto entity : entities)
    {
      unordered_map<string,json *> components = entity.second;

      json &position = *components["position"];
      json &velocity = *components["velocity"];
      
      position["x"] = position["x"].get<float>() + velocity["x"].get<float>() * time_delta;
      position["y"] = position["y"].get<float>() + velocity["y"].get<float>() * time_delta;
      position["z"] = position["z"].get<float>() + velocity["z"].get<float>() * time_delta;

      json &orientation = *components["orientation"];
      json &torque = *components["torque"];
      orientation["pitch"] = orientation["pitch"].get<float>() + torque["pitch"].get<float>() * time_delta;
      orientation["roll"] = orientation["roll"].get<float>() + torque["roll"].get<float>() * time_delta;
      orientation["yaw"] = orientation["yaw"].get<float>() + torque["yaw"].get<float>() * time_delta;
    }
  }

  void Physics::velocityApply(json const& message)
  {
    json &velocity = *entities[message["entity_id"]]["velocity"];
    velocity["x"] = velocity["x"].get<float>() + message["x"].get<float>();
    velocity["y"] = velocity["y"].get<float>() + message["y"].get<float>();
    velocity["z"] = velocity["z"].get<float>() + message["z"].get<float>();
  }
}
