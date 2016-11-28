#include "Engine/component.hpp"
#include "Engine/system.hpp"
#include "Systems/graphics.hpp"
#include "Systems/input.hpp"

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
