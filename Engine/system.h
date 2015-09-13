/* system.h -
 *   System objects are intended to manage subsets of Component objects. These
 * subsets can be used for virtually anything, be it collision detection, input,
 * or anything else.
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
    enum state_type
    {
      SHUTDOWN = 0,
      RUNNING = 1,
      ERROR = 2
    };
    System();
    virtual ~System() {};
    void recvMsg(Message const& msg);

  private:
    virtual void initialize() = 0;
    virtual void update(float delta) = 0;
    void *(*callbacks)(Message const& msg);

  // Static members
  public:
    static void initAll();
    static void updateAll();
    static inline System::state_type getState() { return state; }
    // TODO Evalue whether it is necessary to have System::sendMsg()

  private:
    static vector<System *> systems;
    static high_resolution_clock::time_point lastTime;
    static System::state_type state;
  };
}

#endif // _SYSTEM_H
