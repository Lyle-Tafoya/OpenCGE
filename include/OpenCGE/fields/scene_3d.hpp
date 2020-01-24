#ifndef OPENCGE_FIELD_SCENE_3D_HPP_
#define OPENCGE_FIELD_SCENE_3D_HPP_

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <GL/glu.h>

namespace OpenCGE::Field
{
  struct Scene3D
  {
    std::vector<std::vector<glm::vec3>> meshes;
    GLuint displayListIndex;
  };
}

#endif
