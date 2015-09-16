/* component.h -
 *   Component objects are used to store data to be used by System objects.
 */

#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <json/json.h>
#include <string>
  using std::string;

#include "message.h"

namespace OpenCGE
{
  class Component
  {
  public:
    Component();
    virtual ~Component() {};

  private:
    Json::Value data;

  // Static members
  public:
    // Load components from JSON files into memory
    static bool load(string const& filePath);
    static bool loadAll(string const& directoryPath);

  private:
    static Json::Value components; // A place to hold a base copy of all our components in memory
  };
}
#endif
