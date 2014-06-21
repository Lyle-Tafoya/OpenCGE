/* message.h -
 *   'message' objects are used for communication between 'component' and
 *   'system' objects.
*/

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <vector>
  using std::vector;

namespace OpenCGE
{
  class message
  {
    // Parameter 0 will be used for the message id
    vector<int> parameters;
  };
}

#endif
