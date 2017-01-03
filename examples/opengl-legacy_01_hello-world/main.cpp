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
  Physics physics_system;
  GraphicsOpenGLLegacy graphics_system;
  graphics_system.scenesLoad("assets/models");

  // Create a new entity
  size_t entity_id = System::entityCreate("object_3d");
  System::callbackTrigger({{"type_id","scene_update"},{"entity_id",entity_id},{"scene_name","hello_world"}});
  System::callbackTrigger({{"type_id","torque_apply"},{"entity_id",entity_id},{"x",50.f},{"y",50.f},{"z",0.f}});
  System::callbackTrigger({{"type_id","velocity_apply"},{"entity_id",entity_id},{"x",0.f},{"y",0.f},{"z",-0.1f}});

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
  }

  System::callbackTrigger({{"type_id","shutdown"}});
}
