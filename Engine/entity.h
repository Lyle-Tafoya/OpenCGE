/* entity.h -
 * 		Entity objects are nothing more than an id and an aggregate of all
 * Components registered with this Entity id.
*/

#ifndef _ENTITY_H
#define _ENTITY_H

#include <iostream>
#include <vector>
  using std::vector;
#include <string>
  using std::string;
#include "component.h"

namespace OpenCGE
{
  class Entity
  {
  public:
    Entity();
    inline size_t getId() { return id; }

  private:
    vector<Component *> components; // TODO Change Entity.components from vector to json/hash map
    size_t id;

  // Static fields
  public:
    static void disassemble(Entity const& entity);
    static void assemble(size_t type); // TODO Entity type definitions should come from json files
    static void assemble(string type);

  private:
    static vector<Entity *> entities; // TODO Perform analysis of Entity::entities. Needed or unnecessary?
  };
}

#endif
