#ifndef _INPUT_H
#define _INPUT_H

#include <vector>
  using std::vector;

#include "../Engine/system.h"
#include "../Components/controller.h"

namespace OpenCGE
{
  class input : public system
  {
    void Init();
    void Update(float delta);

    vector<controller *> controllers;
  };
}

#endif
