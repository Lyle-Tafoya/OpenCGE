#ifndef _INPUT_H
#define _INPUT_H

#include <vector>
  using std::vector;

#include "../Engine/system.hpp"

namespace OpenCGE
{
  // Detects input and passes it along to registered callback functions
  class Input : public System
  {
    void initialize();
    void update(float delta);
  };
}

#endif
