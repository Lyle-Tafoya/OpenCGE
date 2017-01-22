#include <OpenCGE/physics.hpp>

namespace OpenCGE
{

  Physics::Physics()
    : System("physics")
  {
    callbackRegister("position_update", &Physics::positionUpdate, this);
    callbackRegister("torque_apply", &Physics::torqueApply, this);
    callbackRegister("time_passed", &Physics::update, this);
    callbackRegister("velocity_apply", &Physics::velocityApply, this);
  }

  void Physics::entityAdd(size_t entity_id)
  {
    std::unordered_map<std::string, void *> &entity = entities[entity_id];

    Field::Point3D *orientation = (Field::Point3D *)entity["orientation"];
    if(orientation == nullptr)
    {
      orientation = new Field::Point3D(0.f, 0.f, 0.f);
      entity["orientation"] = orientation;
    }
    Field::Point3D *position = (Field::Point3D *)entity["position"];
    if(position == nullptr)
    {
      position = new Field::Point3D(0.f, 0.f, 0.f);
      entity["position"] = position;
    }
    Field::Point3D *torque = (Field::Point3D *)entity["torque"];
    if(torque == nullptr)
    {
      torque = new Field::Point3D(0.f, 0.f, 0.f);
      entity["torque"] = torque;
    }
    Field::Point3D *velocity = (Field::Point3D *)entity["velocity"];
    if(velocity == nullptr)
    {
      velocity = new Field::Point3D(0.f, 0.f, 0.f);
      entity["velocity"] = velocity;
    }

    components[entity_id] = new Component::Physics(*orientation, *position, *torque, *velocity);
  }

  void Physics::entityRemove(size_t entity_id)
  {
    delete components[entity_id];
    components.erase(entity_id);
  }

  void Physics::positionUpdate(nlohmann::json const& message)
  {
    size_t entity_id = message["entity_id"];
    auto &position = components[entity_id]->position;

    position.x = message["x"];
    position.y = message["y"];
    position.z = message["z"];
  }

  void Physics::torqueApply(nlohmann::json const& message)
  {
    size_t entity_id = message["entity_id"];
    Field::Point3D &torque = components[entity_id]->torque;

    torque.x += message["x"].get<float>();
    torque.y += message["y"].get<float>();
    torque.z += message["z"].get<float>();
  }

  void Physics::update(nlohmann::json const& message)
  {
    float time_delta = message["time_delta"];
    for(auto entity : components)
    {
      Component::Physics &component = *entity.second;

      component.position.x += component.velocity.x * time_delta;
      component.position.y += component.velocity.y * time_delta;
      component.position.z += component.velocity.z * time_delta;

      component.orientation.x += component.torque.x * time_delta;
      component.orientation.y += component.torque.y * time_delta;
      component.orientation.z += component.torque.z * time_delta;
    }
  }

  void Physics::velocityApply(nlohmann::json const& message)
  {
    size_t entity_id = message["entity_id"];
    Field::Point3D &velocity = components[entity_id]->velocity;

    velocity.x += message["x"].get<float>();
    velocity.y += message["y"].get<float>();
    velocity.z += message["z"].get<float>();
  }
}
