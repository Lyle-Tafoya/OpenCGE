#include <boost/algorithm/string.hpp>
 using boost::split;
 using boost::is_any_of;
#include <boost/regex.hpp>
 using boost::regex;
#include <boost/algorithm/string/regex.hpp>
 using boost::split_regex;
#include <vector>
 using std::vector;
#include <fstream>
 using std::ifstream;
#include "system.hpp"

namespace OpenCGE
{
  json System::component_templates;

  //json System::component_templates;
  void System::callbackTrigger(json const& message)
  {
  }

  void System::componentCreate(string const& component_name, string const& entity_id)
  {
  }

  void System::componentDelete(string const& component_name, string const& entity_id)
  {
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
  }

  void System::componentsLoad(string const& directory_path)
  {
  }

  void System::componentsUnload()
  {
  }

  void System::entitiesLoad(string const& directory_path)
  {
  }

  void System::entitiesUnload()
  {
  }

  string System::entityCreate(string const& entity_name)
  {
  }

  void System::entityDelete(string const& entity_delete)
  {
  }

  void System::entityLoad(string const& file_path)
  {
  }

  void System::entityUnload(string const& entity_name)
  {
  }

}
