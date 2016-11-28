#include <unordered_map>
#include <fstream>
  using std::ifstream;
#include "component.hpp"

namespace OpenCGE
{
  json Component::components;

  Component::Component(string const& type)
  {
    data = components[type];
  }

  // Instantiate a component and return a pointer to it
  Component* Component::get(string const& type)
  {
    Component *component = new Component(type);
    if(component->data.is_null())
    {
      // TODO Implement proper error handling for Component::get
      delete component;
      return nullptr;
    }
    else
    {
      return component;
    }
  }

  // Load a component from a JSON file into memory
  bool Component::load(string const& filePath)
  {
    json jsonData;
    ifstream jsonFile(filePath, ifstream::binary);
    while(!jsonFile.eof())
    {
      jsonFile >> jsonData;
    }

    if(jsonData["name"].is_null())
    {
      return false;
    }

    //components[jsonData["name"]] = jsonData;
    components["potato"] = jsonData;
    return true;
  }

  // Load all components from JSON files in a given directory
  bool Component::loadAll(string const& directoryPath)
  {
    return false;
  }

}
