#include "../../Engine/system.hpp"
using namespace OpenCGE;

int main()
{
  System::componentsLoad("Data/Components");
  System::entitiesLoad("Data/Entities");
  return 0;
}
