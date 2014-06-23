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
  private:
    vector<Component *> components[];

  protected:
    size_t id;

  public:
    Entity();

  // Static fields
  private:
    static vector<Entity *> entities;
    static void Delete(size_t id);
    static void New(size_t type);
  };
}

#endif
