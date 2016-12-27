#include <unistd.h>
#include <chrono>
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;
  using std::chrono::time_point;
#include <OpenCGE/system.hpp>
#include <OpenCGE/graphics_opengl_legacy.hpp>
#include <OpenCGE/physics.hpp>
  using namespace OpenCGE;

int main()
{
  // Load components and entities
  System::componentsLoad("data/components");
  System::entitiesLoad("data/entities");

  // Instantiate our systems
  GraphicsOpenGLLegacy graphics_system;
  Physics physics_system;

  // Timing
  high_resolution_clock timer;
  auto program_start = timer.now();
  auto current_time = program_start, previous_time = program_start;
  float delta_time = 0.f;

  // Main loop
  while(true)
  {
    previous_time = current_time;
    current_time = timer.now();
    delta_time = duration_cast<milliseconds>(current_time - previous_time).count() / 1000.f;
    System::callbackTrigger({{"type_id","time_passed"},{"time_delta",delta_time}});
    sleep(1);
  }

  System::callbackTrigger({{"type_id","shutdown"}});
}
