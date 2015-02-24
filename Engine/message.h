/* message.h -
 *   'message' objects are used for communication between 'component' and
 *   'system' objects.
*/

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <vector>
  using std::vector;
#include <string>
  using std::string;

namespace OpenCGE
{
  class Message
  {
  public:
    inline size_t GetType() const { return type; }
    inline string const& GetBody() const { return body; }

  private:
    size_t type;
    string body;
  };
}

#endif
