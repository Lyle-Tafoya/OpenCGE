#include <fstream>
using std::ifstream;
#include "entity.h"

namespace OpenCGE
{
  Json::Value Entity::entities;

  // Constructor
  Entity::Entity()
  {
  }

  bool Entity::load(string const& filePath)
  {
    Json::Value jsonData;
    Json::Reader reader;
    ifstream jsonFile(filePath, ifstream::binary);
    bool parsingSuccessful = reader.parse(jsonFile, jsonData, false);
    if(parsingSuccessful == false || jsonData["name"].isNull() || jsonData["components"].isNull())
    {
      return false;
    }
    entities[jsonData["name"].asString()] = jsonData["components"];
    return true;
  }
  
  bool Entity::loadAll(string const& directoryPath)
  {
    return false;
  }
  
  // Delete an existing entity with a known id
  void Entity::disassemble(Entity const& entity)
  {
  }

  Entity *Entity::assemble(string const& type)
  {
    /*
    Json::Value required_components = entities["components"];
    for(auto component : required_componets)
    {
      
    }*/
  }
}
