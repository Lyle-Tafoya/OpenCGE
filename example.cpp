#include "Engine/system.h"
#include "Engine/component.h"
#include "Systems/graphics.h"
//#include "Systems/graphics_legacy.h"
#include "Systems/input.h"

using namespace OpenCGE;

int main()
{
  // Create all the systems that will be used
  Graphics graphicsSystem(800, 600, "Hello World"); // OpenGL 3.0+
  //GraphicsLegacy graphicsSystem(800, 600, "Hello World"); // OpenGL 2.1+
  Input inputSystem;

  // Initialize all the systems that have been created already
  System::initAll();

  while(System::getState() == System::state_type::RUNNING)
    System::updateAll();
}
