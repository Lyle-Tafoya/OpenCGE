#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "message.h"

namespace OpenCGE
{
  class component
  {
    size_t id;

  public:
    void Send(message const& msg);
    virtual void Recv(message const& msg) = 0;
    virtual ~component();
  };
}
#endif
