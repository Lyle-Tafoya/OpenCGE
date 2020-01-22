#ifndef OPENCGE_SYSTEM_HPP_
#define OPENCGE_SYSTEM_HPP_

#include <chrono>
#include <filesystem>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

#include <OpenCGE/reusable_id_manager.hpp>

namespace OpenCGE
{
  class System
  {
  public:
    static void callbackTrigger(const std::string &messageType, const nlohmann::json &message);
    static void componentCreate(const std::string &componentName, size_t entityId);
    static void componentDelete(const std::string &componentName, size_t entityId);
    static void entitiesLoad(const std::filesystem::path &directoryPath);
    static void entitiesUnload();
    static size_t entityCreate(const std::string &entityName);
    static void entityDelete(size_t entityId);
    static void entityLoad(const std::filesystem::path &filePath);
    static void entityUnload(const std::string &entityName);
    static float getTimeDelta();
    static void timerStart();
    virtual ~System(){};

  protected:
    typedef std::unordered_map<std::string, void *> Entity;
    const std::string NAME;

    System(const std::string &name);
    virtual void entityAdd(size_t entityId) = 0;
    virtual void entityRemove(size_t entityId) = 0;
    void selfRegister();

    template<typename A, typename B>
    static void callbackRegister(const std::string &messageType, A method, B object)
    {
      callbackRegistry[messageType].push_back(std::bind(method, object, std::placeholders::_1));
    }
    template<typename T>
    static T *ensureFieldExists(Entity &entity, const std::string &fieldName)
    {
      T *field = static_cast<T *>(entity[fieldName]);
      if(field == nullptr)
      {
        field = new T();
        entity[fieldName] = field;
      }
      return field;
    }
    static std::unordered_map<size_t, Entity> entities;

  private:
    static std::unordered_map<std::string,std::vector<std::function<void(nlohmann::json const&)>>> callbackRegistry;
    static std::unordered_map<size_t, std::vector<System *>> entityRegistry;
    static std::unordered_map<std::string, std::vector<std::string>> entityTemplates;
    static std::chrono::high_resolution_clock timer;
    static std::chrono::time_point<std::chrono::system_clock> previousTime;
    static std::chrono::time_point<std::chrono::system_clock> currentTime;
    static ReusableIdManager entityIdManager;
    static std::unordered_map<std::string, System *> systemRegistry;
  };
}

#endif
