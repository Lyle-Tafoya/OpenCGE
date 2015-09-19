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
#include <json/json.h>
#include "component.h"
  
namespace OpenCGE
{
  class Entity
  {
  public:
    Entity();
    inline size_t getId() { return id; }

  private:
    Json::Value components;
    size_t id;

  // Static fields
  public:
    static bool load(string const& filePath);
    static bool loadAll(string const& directoryPath);
    static void disassemble(Entity const& entity);
    static Entity *assemble(string const& type);

  private:
    static Json::Value entities;
  };
}

#endif
