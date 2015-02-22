#include "system.h"

namespace OpenCGE
{
  vector<System *> System::systems;
  high_resolution_clock::time_point System::lastTime;

  System::System()
  {
    systems.push_back(this);
  }

  // TODO This should take extra parameters to initialize
  void System::InitAll()
  {
    for(auto &sys : systems)
      sys->Init();
    lastTime = high_resolution_clock::now();
  }

  // Update all the systems
  void System::UpdateAll()
  {
    high_resolution_clock::time_point currentTime = high_resolution_clock::now();
    duration<float> time_span = duration_cast<duration<float>>(currentTime-lastTime);
    float delta = time_span.count();
    lastTime = currentTime;

    // Update all our systems with the time delta
    for(auto &sys : systems)
      sys->Update(delta);
  }
}
