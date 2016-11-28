/* component.h -
 *   Component objects are used to store data to be used by System objects.
 */

#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>
  using std::string;
#include "json.hpp"
  using nlohmann::json;

#include "message.hpp"

namespace OpenCGE
{
  class Component
  {
  public:
    Component(string const& type);
    virtual ~Component() {};
    json const& operator[](string const& key) const { return data[key]; }

  private:
    json data;

  // Static members
  public:
    static bool load(string const& filePath);
    static bool loadAll(string const& directoryPath);
    static Component* get(string const& type);

  private:
    static json components; // A place to hold a base copy of all our components in memory
  };
}
#endif
