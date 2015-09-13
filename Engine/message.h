/* message.h -
 *   Message objects are used for communication to/from systems
*/

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <vector>
  using std::vector;
#include <string>
  using std::string;
#include <json/json.h>

namespace OpenCGE
{
  class Message
  {
  public:
    inline size_t getType() const { return type; }
    inline Json::Value const& getBody() const { return body; }
    // TODO Overload Message::[] to provide read-only access to the json/hash map

  private:
    size_t type;
    Json::Value body;
  };
}

#endif
