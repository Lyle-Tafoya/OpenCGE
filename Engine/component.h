#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <cstddef>
  using std::size_t;

#include "message.h"

namespace OpenCGE
{
  class Component
  {
  public:
    Component();
    void SendMsg(Message const& msg);
    void RecvMsg(Message const& msg);
    virtual ~Component() {};

  private:
    size_t id;
    void *(*callbacks)(Message const& msg);
  };
}
#endif
