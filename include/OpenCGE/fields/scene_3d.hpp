#ifndef INCLUDE_OPENCGE_FIELDS_SCENE_3D_HPP_
#define INCLUDE_OPENCGE_FIELDS_SCENE_3D_HPP_

#include <assimp/scene.h>
#include <glm/glm.hpp>

namespace OpenCGE
{
  namespace Field
  {
    struct Scene3D
    {
      std::vector<std::vector<glm::vec3>> meshes;
    };
  }
}

#endif /* INCLUDE_OPENCGE_FIELDS_SCENE_3D_HPP_ */
