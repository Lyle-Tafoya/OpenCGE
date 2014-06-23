#ifndef _DRAWABLE_H
#define _DRAWABLE_H

#include "../Engine/component.h"

namespace OpenCGE
{
  class Drawable : public Component
  {
    void Recv(message const& msg);
    float x;
    float y;
  };
}

#endif
