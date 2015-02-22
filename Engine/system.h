/* system.h -
 *   'system' based objects are intended to manage subsets of 'entity' objects.
 * These subsets can be used for virtually anything, be it collision detection,
 * input, or anything else.
*/

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <vector>
  using std::vector;
#include <chrono>
  using std::chrono::high_resolution_clock;
  using std::chrono::duration;
  using std::chrono::duration_cast;

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
  public:
    static void InitAll();
    static void UpdateAll();
    static vector<System *> systems;
  private:
    static high_resolution_clock::time_point lastTime;
  };
}

#endif // _SYSTEM_H
