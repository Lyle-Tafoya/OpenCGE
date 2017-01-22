#ifndef INCLUDE_OPENCGE_FIELDS_SCENE_3D_HPP_
#define INCLUDE_OPENCGE_FIELDS_SCENE_3D_HPP_

#include <assimp/scene.h>

namespace OpenCGE
{
  namespace Field
  {
    struct Scene3D
    {
      std::vector<std::vector<Field::Point3D>> meshes;
    };
  }
}

#endif /* INCLUDE_OPENCGE_FIELDS_SCENE_3D_HPP_ */
