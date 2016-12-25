/* system.h -
 *   System objects are intended to manage subsets of Component objects. These
 * subsets can be used for virtually anything, be it collision detection, input,
 * or anything else.
*/

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <string>
  using std::string;
#include "json.hpp"
  using nlohmann::json;

namespace OpenCGE
{
  class System
  {
  // Static members
  public:
    static void callbackTrigger(json const& message);
    static void componentCreate(string const& component_name, string const& entity_id);
    static void componentDelete(string const& component_name, string const& entity_id);
    static void componentLoad(string const& file_path);
    static void componentUnload(string const& component_name);
    static void componentsLoad(string const& directory_path);
    static void componentsUnload();
    static void entitiesLoad(string const& directory_path);
    static void entitiesUnload();
    static string entityCreate(string const& entity_name);
    static void entityDelete(string const& entity_delete);
    static void entityLoad(string const& file_path);
    static void entityUnload(string const& entity_name);

  protected:
    static void callbackRegister(string const& message_type, void *(*callback)(json message));

  private:
    static json callback_registry;
    static json component_registry;
    static json component_templates;
    static size_t entity_count;
    static json entity_registry;
    static json entity_templates;

    static void *(*callbacks)(Message const& msg);
  };
}

#endif // _SYSTEM_H
