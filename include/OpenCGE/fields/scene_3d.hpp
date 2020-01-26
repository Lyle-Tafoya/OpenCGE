#ifndef OPENCGE_FIELD_SCENE_3D_HPP_
#define OPENCGE_FIELD_SCENE_3D_HPP_

#include <assimp/scene.h>
#include <glm/glm.hpp>

namespace OpenCGE::Field
{
  struct Scene3D
  {
    struct Texture
    {
      size_t width;
      size_t height;
      size_t numChannels;
      unsigned char *data;
    };
    struct Model
    {
      std::vector<glm::vec3> mesh;
      std::vector<glm::vec3> textureCoordinates;
      Texture texture;
    };
    std::vector<Model> models;
  };
}

#endif
