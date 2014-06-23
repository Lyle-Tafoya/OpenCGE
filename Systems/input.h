#ifndef _INPUT_H
#define _INPUT_H

#include <vector>
  using std::vector;

#include "../Engine/system.h"
#include "../Components/controller.h"

namespace OpenCGE
{
  // Detects input and passes it along to controller components
  class Input : public System
  {
    void Init();
    void Update(float delta);

    vector<Controller *> controllers;
  };
}

#endif
