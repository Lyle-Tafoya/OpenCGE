#ifndef INCLUDE_OPENCGE_COMPONENTS_SCENE3D_HPP_
#define INCLUDE_OPENCGE_COMPONENTS_SCENE3D_HPP_

#include <assimp/scene.h>

namespace OpenCGE
{
  namespace Components
  {
    struct Scene3D
    {
      aiScene *scene_data;
    };
  }
}

#endif /* INCLUDE_OPENCGE_COMPONENTS_SCENE3D_HPP_ */
