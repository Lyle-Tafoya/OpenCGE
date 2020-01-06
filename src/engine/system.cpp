#include <filesystem>
#include <fstream>
#include <unordered_set>

#include <OpenCGE/system.hpp>

namespace OpenCGE
{
  std::unordered_map<std::string,std::vector<std::function<void(const nlohmann::json &)>>> System::callbackRegistry;
  std::unordered_map<size_t,std::unordered_map<std::string, void *>> System::entities;
  std::unordered_map<size_t,std::vector<System *>> System::entityRegistry;
  std::unordered_map<std::string, std::vector<std::string>> System::entityTemplates;
  std::chrono::high_resolution_clock System::timer;
  std::chrono::time_point<std::chrono::system_clock> System::previousTime;
  std::chrono::time_point<std::chrono::system_clock> System::currentTime;
  std::unordered_map<std::string,std::vector<System *>> System::systemRegistry;
  ReusableIdManager System::entityIdManager;

  System::System(const std::string &name)
    : NAME(name)
  {
    selfRegister();
  }

  void System::callbackTrigger(const std::string &messageType, const nlohmann::json &message)
  {
    for(auto callbackMethod : callbackRegistry[messageType])
    {
      callbackMethod(message);
    }
  }

  void System::componentCreate(const std::string &componentName, size_t entityId)
  {
    for(System *system : systemRegistry[componentName])
    {
      system->entityAdd(entityId);
    }
  }

  void System::componentDelete(const std::string &componentName, size_t entityId)
  {
    for(System *system : systemRegistry[componentName])
    {
      system->entityRemove(entityId);
    }
  }

  void System::entitiesLoad(const std::filesystem::path &directoryPath)
  {
    for(auto &directoryEntry : std::filesystem::directory_iterator(directoryPath))
    {
      System::entityLoad(directoryEntry.path());
    }
  }

  void System::entitiesUnload()
  {
    entityTemplates.clear();
  }

  size_t System::entityCreate(const std::string &entityName)
  {
    size_t entityId = entityIdManager.getId();
    std::vector<System *> &entity = entityRegistry[entityId];
    for(std::string componentName : entityTemplates[entityName])
    {
      for(System *system : systemRegistry[componentName])
      {
        entity.push_back(system);
        system->entityAdd(entityId);
      }
    }

    return entityId;
  }

  void System::entityDelete(size_t entityId)
  {
    for(System *system : entityRegistry[entityId])
    {
      system->entityRemove(entityId);
    }
    entityRegistry.erase(entityId);
    // TODO Delete all fields associated with entity
  }

  void System::entityLoad(const std::filesystem::path &filePath)
  {
    std::ifstream file(filePath);
    std::vector<std::string> &entityTemplate = entityTemplates[filePath];
    for(std::string line; std::getline(file, line);)
    {
      entityTemplate.push_back(line);
    }
  }

  void System::entityUnload(const std::string &entityName)
  {
    entityTemplates.erase(entityName);
  }

  float System::getTimeDelta()
  {
    previousTime = currentTime;
    currentTime = timer.now();
    return (float)std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime).count() / 1000000.f;
  }

  void System::selfRegister()
  {
    systemRegistry[NAME].push_back(this);
  }

  void System::timerStart()
  {
    previousTime = timer.now();
    currentTime = previousTime;
  }

}
