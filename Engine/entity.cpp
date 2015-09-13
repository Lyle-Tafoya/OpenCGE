#include "entity.h"

namespace OpenCGE
{
  vector<Entity *> Entity::entities;

  // Constructor
  Entity::Entity()
  {
    id = entities.size();
    entities.push_back(this); // Register the entity with the 'entities' vector
  }

  // Delete an existing entity with a known id
  void Entity::disassemble(Entity const& entity)
  {
    // Swap the element we want to delete with the last element before deleting
    // This saves us the time it would otherwise take to rearrange the vector
    size_t id = entity.id;
    Entity *tmp = entities[id];
    entities[id] = entities.back();
    entities[id]->id = id;
    entities.pop_back();
    delete tmp;
  }

  // Create a new entity of a certain type
  void Entity::assemble(size_t type)
  {
  }
  void Entity::assemble(string type)
  {
  }
}
