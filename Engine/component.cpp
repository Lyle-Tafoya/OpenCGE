#include <fstream>
  using std::ifstream;
#include "component.h"

namespace OpenCGE
{
  Json::Value Component::components;

  bool Component::load(string const& filePath)
  {
    Json::Value jsonData;
    Json::Reader reader;
    ifstream jsonFile(filePath, ifstream::binary);
    bool parsingSuccessful = reader.parse(jsonFile, jsonData, false);
    if(parsingSuccessful == false || jsonData["name"].isNull())
    {
      return false;
    }
    components[jsonData["name"].asString()] = jsonData;
    return true;
  }

  bool Component::loadAll(string const& directoryPath)
  {
    return false;
  }

}
