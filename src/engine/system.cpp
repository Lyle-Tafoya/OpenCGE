#include <fstream>
  using std::ifstream;
#include <unordered_set>
  using std::unordered_set;
#include <boost/algorithm/string.hpp>
  using boost::split;
  using boost::is_any_of;
#include <boost/regex.hpp>
  using boost::regex;
#include <boost/algorithm/string/regex.hpp>
  using boost::split_regex;
#include <boost/filesystem.hpp>
  using boost::make_iterator_range;
  using boost::filesystem::path;
  using boost::filesystem::directory_iterator;
#include <OpenCGE/system.hpp>


namespace OpenCGE
{
  unordered_map<string,vector<function<void(Json &)>>> System::callback_registry;
  unordered_map<string,vector<System *>> System::component_registry;
  unordered_map<string,Json *> System::component_templates;
  size_t System::entity_count = 0;
  unordered_map<size_t,vector<System *>> System::entity_registry;
  unordered_map<string,Json *> System::entity_templates;

  void System::callbackTrigger(Json & message)
  {
    string *message_type = (string *)message["type_id"];
    for(auto callback_method : callback_registry[*message_type])
    {
      callback_method(message);
    }
  }

  void System::callbackTrigger(json const& message)
  {
    callbackTrigger(jsonConvert(message));
  }

  void System::componentCreate(string const& component_name, size_t entity_id)
  {
    Json *new_component = new Json();
    *new_component = *component_templates[component_name];
    for(System *system : component_registry[component_name])
    {
      system->componentAdd(component_name, new_component, entity_id);
    }
  }

  void System::componentDelete(string const& component_name, size_t entity_id)
  {
    for(System *system : component_registry[component_name])
    {
      system->componentRemove(component_name, entity_id);
    }
  }

  void System::componentLoad(string const& file_path)
  {
    vector<string> fields;
    split_regex(fields, file_path, regex("\\.json"));
    string component_name = fields.front();
    split(fields, component_name, is_any_of("/"));
    component_name = fields.back();
    ifstream file(file_path);
    json j;
    file >> j;
    component_templates[component_name] = &System::jsonConvert(j);
  }

  void System::componentUnload(string const& component_name)
  {
    component_templates.erase(component_name);
  }

  void System::componentsLoad(string const& directory_path)
  {
    path component_directory(directory_path);
    for(auto &dir_entry : make_iterator_range(directory_iterator(component_directory), {}))
    {
      System::componentLoad(dir_entry.path().string());
    }
  }

  void System::entitiesLoad(string const& directory_path)
  {
    path entity_directory(directory_path);
    for(auto &dir_entry : make_iterator_range(directory_iterator(entity_directory), {}))
    {
      System::entityLoad(dir_entry.path().string());
    }
  }

  void System::entitiesUnload()
  {
    entity_templates.clear();
  }

  size_t System::entityCreate(string const& entity_name)
  {
    size_t entity_id = entity_count++;
    unordered_set<System *> entity_systems_set;
    Json &entity_definition = *entity_templates[entity_name];
    vector<string> &components = *(vector<string> *)entity_definition["components"];
    for(string component_name : components)
    {
      for(System *system : component_registry[component_name])
      {
        entity_systems_set.insert(system);
      }
      System::componentCreate(component_name, entity_id);
    }
    vector<System *> entity_systems(entity_systems_set.begin(), entity_systems_set.end());
    entity_registry[entity_id] = entity_systems;

    return entity_id;
  }
  
  void System::entityDelete(size_t entity_id)
  {
    for(System *system : entity_registry[entity_id])
    {
      system->entityRemove(entity_id);
    }
    entity_registry.erase(entity_id);
  }

  void System::entityLoad(string const& file_path)
  {
    vector<string> fields;
    split_regex(fields, file_path, regex("\\.json"));
    string entity_name = fields.front();
    split(fields, entity_name, is_any_of("/"));
    entity_name = fields.back();
    ifstream file(file_path);
    json j;
    file >> j;
    entity_templates[entity_name] = &System::jsonConvert(j);
  }

  void System::entityUnload(string const& entity_name)
  {
    entity_templates.erase(entity_name);
  }

  void System::componentAdd(string const& component_name, Json * component, size_t entity_id)
  {
    entities[entity_id][component_name] = component;
    //(*entities[entity_id])[component_name] = component;
  }

  void System::componentRemove(string const& component_name, size_t entity_id)
  {
    entities[entity_id].erase(component_name);
  }

  void System::entityRemove(size_t entity_id)
  {
    entities.erase(entity_id);
  }

  void System::componentsRegister(vector<string> const& valid_components)
  {
    for(string component_name : valid_components)
    {
      component_registry[component_name].push_back(this);
    }
  }

  Json & System::jsonConvert(json const& j)
  {
    Json *result = new Json();
    for(json::const_iterator node = j.begin(); node != j.end(); ++node)
    {
      void *value = nullptr;
      switch(node.value().type())
      {
        case json::value_t::string:
          value = new string(node.value().get<string>());
          break;
        case json::value_t::boolean:
          value = new bool(node.value().get<bool>());
          break;
        case json::value_t::array:
          switch(node.value().begin().value().type())
          {
            case json::value_t::string:
              value = new vector<string>();
              for(json::const_iterator it = node.value().begin(); it != node.value().end(); ++it)
              {
                ((vector<string> *)value)->push_back(it.value().get<string>());
              }
              break;
            case json::value_t::boolean:
              continue;
              value = new vector<bool>();
              break;
            case json::value_t::number_integer:
              continue;
              value = new vector<int>();
              break;
            case json::value_t::number_float:
              continue;
              value = new vector<float>();
              break;
            case json::value_t::object:
              continue;
            case json::value_t::null:
              continue;
            case json::value_t::array:
              continue;
            case json::value_t::discarded:
              continue;
          }
          break;
        case json::value_t::number_integer:
          value = new int(node.value().get<int>());
          break;
        case json::value_t::number_float:
          value = new float(node.value().get<float>());
          break;
        case json::value_t::object:
          value = &jsonConvert(node.value());
          break;
        case json::value_t::null:
          value = nullptr;
          break;
        case json::value_t::discarded:
          continue;
      }
      (*result)[node.key()] = value;
    }

    return *result;
  }

}
