#include "system.h"

namespace OpenCGE
{
  vector<System *> System::systems;

  System::System()
  {
    systems.push_back(this);
  }

  // TODO This should take extra parameters to initialize
  void System::Initialize()
  {
    for(auto &sys : systems)
      sys->Init();
  }

  // Update all the systems
  void System::UpdateAll(float delta)
  {
    for(auto &sys : systems)
      sys->Update(delta);
  }
}
