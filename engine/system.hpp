/* system.h -
 *   System objects are intended to manage subsets of Component objects. These
 * subsets can be used for virtually anything, be it collision detection, input,
 * or anything else.
*/

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <string>
  using std::string;
#include <vector>
  using std::vector;
#include <unordered_map>
  using std::unordered_map;
#include <functional>
  using std::placeholders::_1;
  using std::function;

#include "json.hpp"
  using nlohmann::json;

namespace OpenCGE
{
  class System
  {
  public:
    template<typename A, typename B>
    static void callbackRegister(string const& message_type, A method, B object)
    {
      callback_registry[message_type].push_back(bind(method, object, _1));
    }
    static void callbackTrigger(json const& message);
    static void componentCreate(string const& component_name, size_t entity_id);
    static void componentDelete(string const& component_name, size_t entity_id);
    static void componentLoad(string const& file_path);
    static void componentUnload(string const& component_name);
    static void componentsLoad(string const& directory_path);
    static void componentsUnload();
    static void entitiesLoad(string const& directory_path);
    static void entitiesUnload();
    static size_t entityCreate(string const& entity_name);
    static void entityDelete(size_t entity_id);
    static void entityLoad(string const& file_path);
    static void entityUnload(string const& entity_name);

  private:
    static unordered_map<string,vector<function<void(json const&)>>> callback_registry;
    static unordered_map<string,vector<System *>> component_registry;
    static unordered_map<string,json> component_templates;
    static size_t entity_count;
    static unordered_map<size_t,vector<System *>> entity_registry;
    static unordered_map<string,json> entity_templates;

  public:
    void componentAdd(string const& component_name, json component);
    void componentRemove(string const& component_name, size_t entity_id);
    void entityRemove(size_t entity_id);

  protected:
    void componentsRegister(vector<string> const& valid_components);
    unordered_map<size_t,json> entities;
  };
}

#endif // _SYSTEM_H
