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
  std::unordered_map<size_t,std::unordered_map<std::string,void *>> System::entities;
  std::unordered_map<size_t,std::vector<System *>> System::entity_registry;
  std::unordered_map<std::string,std::vector<std::string>> System::entity_templates;
  std::chrono::high_resolution_clock System::timer;
  std::chrono::time_point<std::chrono::system_clock> System::previous_time;
  std::chrono::time_point<std::chrono::system_clock> System::current_time;
  std::unordered_map<std::string,std::vector<System *>> System::system_registry;
  ReusableId System::entity_id_generator;

  System::System(std::string const& name)
    : NAME(name)
  {
    selfRegister();
  }

  void System::callbackTrigger(std::string const& message_type, nlohmann::json const& message)
  {
    for(auto callback_method : callback_registry[message_type])
    {
      callback_method(message);
    }
  }

  void System::componentCreate(std::string const& component_name, size_t entity_id)
  {
    for(System *system : system_registry[component_name])
    {
      system->entityAdd(entity_id);
    }
  }

  void System::componentDelete(std::string const& component_name, size_t entity_id)
  {
    for(System *system : system_registry[component_name])
    {
      system->entityRemove(entity_id);
    }
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
    std::vector<System *> &entity = entity_registry[entity_id];
    for(std::string component_name : entity_templates[entity_name])
    {
      for(System *system : system_registry[component_name])
      {
        entity.push_back(system);
        system->entityAdd(entity_id);
      }
    }

    return entity_id;
  }
  
  void System::entityDelete(size_t entity_id)
  {
    for(System *system : entity_registry[entity_id])
    {
      system->entityRemove(entity_id);
    }
    entity_registry.erase(entity_id);
    // TODO Delete all fields associated with entity
  }

  void System::entityLoad(std::string const& file_path)
  {
    std::vector<std::string> fields;
    std::string entity_name = file_path;
    boost::split(fields, entity_name, boost::is_any_of("/"));
    entity_name = fields.back();
    std::ifstream file(file_path);
    std::vector<std::string> &entity_template = entity_templates[entity_name];
    for(std::string line; std::getline(file, line);)
    {
      entity_template.push_back(line);
    }
  }

  void System::entityUnload(std::string const& entity_name)
  {
    entity_templates.erase(entity_name);
  }

  float System::getTimeDelta()
  {
    previous_time = current_time;
    current_time = timer.now();
    return (float)std::chrono::duration_cast<std::chrono::microseconds>(current_time - previous_time).count() / 1000000.f;
  }

  void System::selfRegister()
  {
    system_registry[NAME].push_back(this);
  }

  void System::timerStart()
  {
    previous_time = timer.now();
    current_time = previous_time;
  }

}
