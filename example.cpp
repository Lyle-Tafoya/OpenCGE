#include "Engine/system.h"
#include "Systems/graphics.h"
#include "Systems/input.h"
using namespace OpenCGE;

int main()
{
  graphics graphicsSystem(1280, 800, "OpenCGE Test");
  input inputSystem();
  system::Initialize();

  float delta = 0.0f;
  while(true)
  {
    system::UpdateAll(delta);
  }
}
