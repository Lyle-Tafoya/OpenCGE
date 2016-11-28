#include <fstream>
  using std::ifstream;
#include "entity.hpp"

namespace OpenCGE
{
  json Entity::entities;

  // Constructor
  Entity::Entity()
  {
  }

  bool Entity::load(string const& filePath)
  {
    json jsonData;
    ifstream jsonFile(filePath, ifstream::binary);
    if(jsonData["name"].is_null() || jsonData["components"].is_null())
    {
      return false;
    }
    entities[jsonData["name"].dump()] = jsonData["components"];
    return true;
  }
  
  bool Entity::loadAll(string const& directoryPath)
  {
    return false;
  }
  
  // Delete an existing entity with a known id
  void Entity::disassemble(Entity const& entity)
  {
    // TODO Entity::disassemble
  }

  // Instantiate an Entity and load it's components
  Entity* Entity::assemble(string const& type)
  {
    Entity *entity = new Entity();
    for(auto component_type : entities[type])
    {
      Component *component = Component::get(type);
      if(component == nullptr)
      {
        // TODO Implement proper error handling for Entity::assemble
        return nullptr;
      }
    }
    return entity;
  }
}
