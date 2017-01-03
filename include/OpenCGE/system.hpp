#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP

#include <string>
  using std::string;
#include <vector>
  using std::vector;
#include <unordered_map>
  using std::unordered_map;
#include <functional>
  using std::placeholders::_1;
  using std::function;
#include <OpenCGE/json.hpp>
  using nlohmann::json;

namespace OpenCGE
{
  typedef unordered_map<string,void *> Json;

  class System
  {
  public:
    template<typename A, typename B>
    static void callbackRegister(string const& message_type, A method, B object)
    {
      callback_registry[message_type].push_back(bind(method, object, _1));
    }
    static void callbackTrigger(Json & message);
    static void callbackTrigger(json const& message);
    static void componentCreate(string const& component_name, size_t entity_id);
    static void componentDelete(string const& component_name, size_t entity_id);
    static void componentLoad(string const& file_path);
    static void componentUnload(string const& component_name);
    static void componentsLoad(string const& directory_path);
    static void entitiesLoad(string const& directory_path);
    static void entitiesUnload();
    static size_t entityCreate(string const& entity_name);
    static void entityDelete(size_t entity_id);
    static void entityLoad(string const& file_path);
    static void entityUnload(string const& entity_name);
    static Json & jsonConvert(json const& j);

  private:
    static unordered_map<string,size_t> message_registry;
    static unordered_map<string,vector<function<void(Json &)>>> callback_registry;
    static unordered_map<string,vector<System *>> component_registry;
    static unordered_map<string,Json *> component_templates;
    static size_t entity_count;
    static unordered_map<size_t,vector<System *>> entity_registry;
    static unordered_map<string,Json *> entity_templates;

  public:
    virtual ~System(){};
    void componentAdd(string const& component_name, Json * component, size_t entity_id);
    void componentRemove(string const& component_name, size_t entity_id);
    void entityRemove(size_t entity_id);

  protected:
    void componentsRegister(vector<string> const& valid_components);
    unordered_map<size_t,unordered_map<string,Json *>> entities;
  };
}

#endif

