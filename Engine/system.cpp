#include "system.h"

namespace OpenCGE
{
  vector<system *> system::systems;

  system::system()
  {
    systems.push_back(this);
  }

  // TODO This should take extra parameters to initialize
  void system::Initialize()
  {
    for(auto &sys : systems)
      sys->Init();
  }

  // Update all the systems
  void system::UpdateAll(float delta)
  {
    for(auto &sys : systems)
      sys->Update(delta);
  }
}
