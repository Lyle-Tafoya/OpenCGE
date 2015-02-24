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
  public:
    enum state
    {
      SHUTDOWN = 0,
      RUNNING = 1,
      ERROR = 2
    };
    System();
    virtual ~System() {};

  private:
    virtual void Init() = 0;
    virtual void Update(float delta) = 0;

  // Static members
  public:
    static void InitAll();
    static void UpdateAll();
    static inline System::state GetState() { return running; }

  private:
    static vector<System *> systems;
    static high_resolution_clock::time_point lastTime;
    static System::state running;
  };
}

#endif // _SYSTEM_H
