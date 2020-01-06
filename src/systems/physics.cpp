#include <glm/glm.hpp>

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

  void Physics::entityAdd(size_t entityId)
  {
    std::unordered_map<std::string, void *> &entity = entities[entityId];

    glm::vec3 *orientation = static_cast<glm::vec3 *>(entity["orientation"]);
    if(orientation == nullptr)
    {
      orientation = new glm::vec3(0.f, 0.f, 0.f);
      entity["orientation"] = orientation;
    }
    glm::vec3 *position = static_cast<glm::vec3 *>(entity["position"]);
    if(position == nullptr)
    {
      position = new glm::vec3(0.f, 0.f, 0.f);
      entity["position"] = position;
    }
    glm::vec3 *torque = static_cast<glm::vec3 *>(entity["torque"]);
    if(torque == nullptr)
    {
      torque = new glm::vec3(0.f, 0.f, 0.f);
      entity["torque"] = torque;
    }
    glm::vec3 *velocity = static_cast<glm::vec3 *>(entity["velocity"]);
    if(velocity == nullptr)
    {
      velocity = new glm::vec3(0.f, 0.f, 0.f);
      entity["velocity"] = velocity;
    }

    components[entityId] = new Component::Physics(*orientation, *position, *torque, *velocity);
  }

  void Physics::entityRemove(size_t entityId)
  {
    delete components[entityId];
    components.erase(entityId);
  }

  void Physics::positionUpdate(const nlohmann::json &message)
  {
    size_t entityId = message["entity_id"];
    auto &position = components[entityId]->position;

    position.x = message["x"].get<float>();
    position.y = message["y"].get<float>();
    position.z = message["z"].get<float>();
  }

  void Physics::torqueApply(const nlohmann::json &message)
  {
    size_t entityId = message["entity_id"];
    glm::vec3 &torque = components[entityId]->torque;

    torque.x += message["x"].get<float>();
    torque.y += message["y"].get<float>();
    torque.z += message["z"].get<float>();
  }

  void Physics::update(const nlohmann::json &message)
  {
    float timeDelta = message["time_delta"];
    for(auto entity : components)
    {
      Component::Physics &component = *entity.second;

      component.position.x += component.velocity.x * timeDelta;
      component.position.y += component.velocity.y * timeDelta;
      component.position.z += component.velocity.z * timeDelta;

      component.orientation.x += component.torque.x * timeDelta;
      component.orientation.y += component.torque.y * timeDelta;
      component.orientation.z += component.torque.z * timeDelta;
    }
  }

  void Physics::velocityApply(const nlohmann::json &message)
  {
    size_t entityId = message["entity_id"];
    glm::vec3 &velocity = components[entityId]->velocity;

    velocity.x += message["x"].get<float>();
    velocity.y += message["y"].get<float>();
    velocity.z += message["z"].get<float>();
  }
}
