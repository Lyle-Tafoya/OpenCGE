/* system.h -
 *   'system' based objects are intended to manage subsets of 'entity' objects.
 * These subsets can be used for virtually anything, be it collision detection,
 * input, or anything else.
*/

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <vector>
  using std::vector;

#include "message.h"

namespace OpenCGE
{
  class System
  {
    virtual void Init() = 0;
    virtual void Update(float delta) = 0;

  public:
    System();
    virtual ~System() {};

    // Static members
    static void Initialize();
    static void UpdateAll(float delta);
    static vector<System *> systems;
  };
}

#endif // _SYSTEM_H
