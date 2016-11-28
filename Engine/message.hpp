/* message.h -
 *   Message objects are used for communication to/from systems
*/

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <vector>
  using std::vector;
#include <string>
  using std::string;
#include "json.hpp"
  using nlohmann::json;

namespace OpenCGE
{
  class Message
  {
  public:
    inline size_t getType() const { return type; }
    inline json const& getBody() const { return body; }
    json const& operator[](string const& key) const { return body[key]; }

  private:
    size_t type;
    json body;
  };
}

#endif
