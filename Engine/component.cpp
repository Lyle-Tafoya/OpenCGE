#include <fstream>
  using std::ifstream;
#include "component.h"

namespace OpenCGE
{
  Json::Value Component::components;

  void Component::load(string const& filePath)
  {
	Json::Value jsonData;
	Json::Reader reader;
	ifstream jsonFile(filePath, ifstream::binary);
	bool parsingSuccessful = reader.parse(jsonFile, jsonData, false);
	components[jsonData["name"].asString()] = jsonData;
  }

  void Component::loadAll(string const& directoryPath)
  {

  }

}
