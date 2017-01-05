#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <functional>
#include <OpenCGE/json.hpp>
#include <OpenCGE/reusable_id.hpp>

namespace OpenCGE
{
  typedef std::unordered_map<std::string,void *> untyped_map;

  class System
  {
  public:
    static void callbackTrigger(untyped_map & message);
    static void callbackTrigger(nlohmann::json const& message);
    static void componentCreate(std::string const& component_name, size_t entity_id);
    static void componentDelete(std::string const& component_name, size_t entity_id);
    static void componentLoad(std::string const& file_path);
    static void componentUnload(std::string const& component_name);
    static void componentsLoad(std::string const& directory_path);
    static void entitiesLoad(std::string const& directory_path);
    static void entitiesUnload();
    static size_t entityCreate(std::string const& entity_name);
    static void entityDelete(size_t entity_id);
    static void entityLoad(std::string const& file_path);
    static void entityUnload(std::string const& entity_name);
    static float getTimeDelta();
    static void timerStart();
    virtual ~System(){};

  protected:
    template<typename A, typename B>
    static void callbackRegister(std::string const& message_type, A method, B object)
    {
      callback_registry[message_type].push_back(std::bind(method, object, std::placeholders::_1));
    }
    void componentAdd(std::string const& component_name, untyped_map * component, size_t entity_id);
    void componentRemove(std::string const& component_name, size_t entity_id);
    void componentsRegister(std::vector<std::string> const& valid_components);
    void entityRemove(size_t entity_id);

    std::unordered_map<size_t,std::unordered_map<std::string,untyped_map *>> entities;

  private:
    static untyped_map & jsonConvert(nlohmann::json const& j);

    static std::unordered_map<std::string,size_t> message_registry;
    static std::unordered_map<std::string,std::vector<std::function<void(untyped_map &)>>> callback_registry;
    static std::unordered_map<std::string,std::vector<System *>> component_registry;
    static std::unordered_map<std::string,untyped_map *> component_templates;
    static std::unordered_map<size_t,std::vector<System *>> entity_registry;
    static std::unordered_map<std::string,untyped_map *> entity_templates;
    static std::chrono::high_resolution_clock timer;
    static std::chrono::time_point<std::chrono::system_clock> previous_time;
    static std::chrono::time_point<std::chrono::system_clock> current_time;
    static ReusableId entity_id_generator;
  };
}

#endif

