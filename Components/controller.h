#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <string>
  using std::string;

#include "../Engine/component.h"

namespace OpenCGE
{
  class Controller : public Component
  {
    void LoadKeymap(string const& filename);

  public:
    void Recv(message const& msg);
  };
}

#endif
