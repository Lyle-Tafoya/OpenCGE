#include <fstream>
#include <unordered_set>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/filesystem.hpp>
#include <OpenCGE/system.hpp>

namespace OpenCGE
{
  std::unordered_map<std::string,std::vector<std::function<void(nlohmann::json const&)>>> System::callback_registry;
  std::unordered_map<std::string,std::function<void *()>> System::component_factory;
  std::unordered_map<std::string,std::vector<System *>> System::component_registry;
  std::unordered_map<size_t,std::vector<System *>> System::entity_registry;
  std::unordered_map<std::string,untyped_map *> System::entity_templates;
  std::chrono::high_resolution_clock System::timer;
  std::chrono::time_point<std::chrono::system_clock> System::previous_time;
  std::chrono::time_point<std::chrono::system_clock> System::current_time;
  ReusableId System::entity_id_generator;

  void System::callbackTrigger(std::string const& message_type, nlohmann::json const& message)
  {
    for(auto callback_method : callback_registry[message_type])
    {
      callback_method(message);
    }
  }

  void System::componentCreate(std::string const& component_name, size_t entity_id)
  {
    void *new_component = component_factory[component_name]();
    for(System *system : component_registry[component_name])
    {
      system->componentAdd(component_name, new_component, entity_id);
    }
  }

  void System::componentDelete(std::string const& component_name, size_t entity_id)
  {
    for(System *system : component_registry[component_name])
    {
      system->componentRemove(component_name, entity_id);
    }
  }

  void System::componentRegister(std::string const& component_name, void *(*method)())
  {
    component_factory[component_name] = *method;
    component_registry[component_name].push_back(this);
  }

  void System::entitiesLoad(std::string const& directory_path)
  {
    boost::filesystem::path entity_directory(directory_path);
    for(auto &dir_entry : boost::make_iterator_range(boost::filesystem::directory_iterator(entity_directory), {}))
    {
      System::entityLoad(dir_entry.path().string());
    }
  }

  void System::entitiesUnload()
  {
    entity_templates.clear();
  }

  size_t System::entityCreate(std::string const& entity_name)
  {
    size_t entity_id = entity_id_generator.getId();
    std::unordered_set<System *> entity_systems_set;
    untyped_map &entity_definition = *entity_templates[entity_name];
    std::vector<std::string> &components = *(std::vector<std::string> *)entity_definition["components"];
    for(std::string component_name : components)
    {
      for(System *system : component_registry[component_name])
      {
        entity_systems_set.insert(system);
      }
      System::componentCreate(component_name, entity_id);
    }
    std::vector<System *> entity_systems(entity_systems_set.begin(), entity_systems_set.end());
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

  void System::entityLoad(std::string const& file_path)
  {
    std::vector<std::string> fields;
    boost::split_regex(fields, file_path, boost::regex("\\.json"));
    std::string entity_name = fields.front();
    boost::split(fields, entity_name, boost::is_any_of("/"));
    entity_name = fields.back();
    std::ifstream file(file_path);
    nlohmann::json j;
    file >> j;
    entity_templates[entity_name] = &System::jsonConvert(j);
  }

  void System::entityUnload(std::string const& entity_name)
  {
    entity_templates.erase(entity_name);
  }

  void System::componentAdd(std::string const& component_name, void * component, size_t entity_id)
  {
    entities[entity_id][component_name] = component;
  }

  void System::componentRemove(std::string const& component_name, size_t entity_id)
  {
    entities[entity_id].erase(component_name);
  }

  void System::entityRemove(size_t entity_id)
  {
    entities.erase(entity_id);
  }

  float System::getTimeDelta()
  {
    previous_time = current_time;
    current_time = timer.now();
    return (float)std::chrono::duration_cast<std::chrono::microseconds>(current_time - previous_time).count() / 1000000.f;
  }

  void System::timerStart()
  {
    previous_time = timer.now();
    current_time = previous_time;
  }

  untyped_map & System::jsonConvert(nlohmann::json const& j)
  {
    untyped_map *result = new untyped_map();
    for(nlohmann::json::const_iterator node = j.begin(); node != j.end(); ++node)
    {
      void *value = nullptr;
      switch(node.value().type())
      {
        case nlohmann::json::value_t::string:
          value = new std::string(node.value().get<std::string>());
          break;
        case nlohmann::json::value_t::boolean:
          value = new bool(node.value().get<bool>());
          break;
        case nlohmann::json::value_t::array:
          switch(node.value().begin().value().type())
          {
            case nlohmann::json::value_t::string:
              value = new std::vector<std::string>();
              for(nlohmann::json::const_iterator it = node.value().begin(); it != node.value().end(); ++it)
              {
                ((std::vector<std::string> *)value)->push_back(it.value().get<std::string>());
              }
              break;
            case nlohmann::json::value_t::boolean:
              continue;
              value = new std::vector<bool>();
              break;
            case nlohmann::json::value_t::number_integer:
              continue;
              value = new std::vector<int>();
              break;
            case nlohmann::json::value_t::number_float:
              continue;
              value = new std::vector<float>();
              break;
            case nlohmann::json::value_t::object:
              continue;
            case nlohmann::json::value_t::null:
              continue;
            case nlohmann::json::value_t::array:
              continue;
            case nlohmann::json::value_t::discarded:
              continue;
          }
          break;
        case nlohmann::json::value_t::number_integer:
          value = new int(node.value().get<int>());
          break;
        case nlohmann::json::value_t::number_float:
          value = new float(node.value().get<float>());
          break;
        case nlohmann::json::value_t::object:
          value = &jsonConvert(node.value());
          break;
        case nlohmann::json::value_t::null:
          value = nullptr;
          break;
        case nlohmann::json::value_t::discarded:
          continue;
      }
      (*result)[node.key()] = value;
    }

    return *result;
  }

}
