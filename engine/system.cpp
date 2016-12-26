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
#include "system.hpp"

namespace OpenCGE
{
  unordered_map<string,vector<function<void(json const&)>>> System::callback_registry;
  unordered_map<string,vector<System *>> System::component_registry;
  unordered_map<string,json> System::component_templates;
  size_t System::entity_count = 0;
  unordered_map<size_t,vector<System *>> System::entity_registry;
  unordered_map<string,json> System::entity_templates;

  void System::callbackTrigger(json const& message)
  {
    for(auto callback_method : callback_registry[message["type_id"]])
    {
      callback_method(message);
    }
  }

  void System::componentCreate(string const& component_name, size_t entity_id)
  {
    json *new_component = new json(component_templates[component_name]);
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
    component_templates[component_name] = j;
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

  void System::componentsUnload()
  {
    component_templates.clear();
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
    for(string component_name : entity_templates[entity_name]["components"])
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
    entity_templates[entity_name] = j;
  }

  void System::entityUnload(string const& entity_name)
  {
    entity_templates.erase(entity_name);
  }

  void System::componentAdd(string const& component_name, json * component, size_t entity_id)
  {
    entities[entity_id][component_name] = component;
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
}

