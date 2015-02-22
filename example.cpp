#include "Engine/system.h"
#include "Systems/graphics.h"
#include "Systems/input.h"

using namespace OpenCGE;

int main()
{
  // Create all the systems that will be used
  Graphics graphicsSystem(800, 600, "Hello World"); // OpenGL 3.0+
  //GraphicsLegacy graphicsSystem(800, 600, "Hello World"); // pre-OpenGL 3.0
  Input inputSystem();

  // Initialize all the systems that have been created already
  System::InitAll();

  while(true)
    System::UpdateAll();
}
