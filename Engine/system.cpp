#include "system.h"

namespace OpenCGE
{
  vector<System *> System::systems;
  high_resolution_clock::time_point System::lastTime;
  System::state_type System::state;

  System::System()
  {
    systems.push_back(this);
  }

  // Initialize all existing systems
  void System::initAll()
  {
    for(auto &sys : systems)
    {
      sys->initialize();
    }
    lastTime = high_resolution_clock::now();
    state = System::state_type::RUNNING;
  }

  // Update all the systems
  void System::updateAll()
  {
    high_resolution_clock::time_point currentTime = high_resolution_clock::now();
    duration<float> timeSpan = duration_cast<duration<float>>(currentTime-lastTime);
    float delta = timeSpan.count();
    lastTime = currentTime;

    // Update all our systems with the time delta
    for(auto &system : systems)
    {
      system->update(delta);
    }
  }
}
