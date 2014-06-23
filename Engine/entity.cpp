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
  void Entity::Delete(size_t id)
  {
    // Swap the element we want to delete with the last element before deleting
    // This saves us the time it would otherwise take to rearrange the vector
    Entity *tmp = entities[id];
    entities[id] = entities.back();
    entities[id]->id = id;
    entities.pop_back();
    delete tmp;
  }

  // Create a new entity of a certain type
  void Entity::New(size_t type)
  {
    // TODO This will read in a table of entity types which will tell us which
    // TODO components we should load automatically. This table will not be a
    // TODO part of the engine, although an example may be provided.
  }
}
