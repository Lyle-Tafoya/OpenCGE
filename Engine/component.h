#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <cstddef>
  using std::size_t;

#include "message.h"

namespace OpenCGE
{
  class Component
  {
    size_t id;

  public:
    Component();
    void Send(message const& msg);
    virtual void Recv(message const& msg) = 0;
    virtual ~Component();
  };
}
#endif
