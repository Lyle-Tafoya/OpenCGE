/* entity.h -
 *   'entity' objects make up everything in a game. This includes players,
 * NPCs, projectiles, platforms, decals, and more. However, the most basic
 * entity is nothing more than an id. In order to add functionality to an
 * entity, you must attach one or more 'component' objects to it.
*/

#ifndef _ENTITY_H
#define _ENTITY_H

#include <iostream>
#include <vector>
  using std::vector;
#include "component.h"

namespace OpenCGE
{
  class Entity
  {
  public:
    Entity();
    inline size_t getId() { return id; }

  private:
    vector<Component *> components;
    size_t id;
    void RecvMsg(Message const& msg);

  // Static fields
  public:
    static void Delete(Entity const& entity);
    static void New(size_t type);

  private:
    static vector<Entity *> entities;
  };
}

#endif
