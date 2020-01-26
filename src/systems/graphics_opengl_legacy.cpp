#include <iostream>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <OpenCGE/graphics_opengl_legacy.hpp>
#include <OpenCGE/glfw_singleton.hpp>

namespace OpenCGE
{
  GraphicsOpenGLLegacy::GraphicsOpenGLLegacy(glm::ivec2 windowDimensions, const std::string &windowName) : System("graphics_3d")
  {
    callbackRegister("scene_update", &GraphicsOpenGLLegacy::sceneUpdate, this);
    callbackRegister("shutdown", &GraphicsOpenGLLegacy::shutdown, this);
    callbackRegister("time_passed", &GraphicsOpenGLLegacy::update, this);

    window = GLFWSingleton::get();
    glfwMakeContextCurrent(window);
    glfwSetWindowSize(window, windowDimensions.x, windowDimensions.y);
    glfwSetWindowTitle(window, windowName.c_str());
    glfwSwapInterval(0);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    windowResize(width, height);

    // Generate default texture
    for(size_t y=0; y < 64; ++y)
    {
      for(size_t x=0; x < 64; ++x)
      {
        unsigned char c = (((y & 0x8)==0) ^ ((x & 0x8) == 0)) * 255;
        textureMissing[y][x][0] = c;
        textureMissing[y][x][1] = 0;
        textureMissing[y][x][2] = c;
        textureMissing[y][x][3] = 255;
      }
    }
    glGenTextures(1, &textureMissingIndex);
    glBindTexture(GL_TEXTURE_2D, textureMissingIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureMissing);
  }

  void GraphicsOpenGLLegacy::entityAdd(size_t entityId)
  {
    Entity &entity = entities[entityId];
    if(entityToDisplayList.size() <= entityId) { entityToDisplayList.resize(entityId+1); }

    auto *orientation = ensureFieldExists<glm::vec3>(entity, "orientation");
    auto *position = ensureFieldExists<glm::vec3>(entity, "position");
    auto *scene = ensureFieldExists<Field::Scene3D>(entity, "scene_3d");

    components[entityId] = new Component::Graphics3D{*orientation, *position, *scene};
  }

  void GraphicsOpenGLLegacy::entityRemove(size_t entityId)
  {
    delete components[entityId];
    components.erase(entityId);
  }

  void GraphicsOpenGLLegacy::windowResize(int width, int height)
  {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, width/height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.f, 0.f, 5.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
  }

  GLuint GraphicsOpenGLLegacy::generateDisplayList(const Field::Scene3D::Model &model, GLuint textureIndex)
  {
    GLuint index = glGenLists(1);
    glNewList(index, GL_COMPILE);
      glBindTexture(GL_TEXTURE_2D, textureIndex);
      glBegin(GL_TRIANGLES);
        size_t numVertices = model.mesh.size();
        bool hasTexture = (model.textureCoordinates.size() > 0);
        for(size_t v = 0; v < numVertices; ++v)
        {
          if(hasTexture)
          {
            glTexCoord3f(model.textureCoordinates[v].x, model.textureCoordinates[v].y, model.textureCoordinates[v].z);
          }
          else
          {
            switch(v%3)
            {
              case 0: glTexCoord2f(0.f, 0.f); break;
              case 1: glTexCoord2f(1.f, 0.f); break;
              case 2: glTexCoord2f(1.f, 1.f); break;
            }
          }
          glVertex3f(model.mesh[v].x, model.mesh[v].y, model.mesh[v].z);
        }
      glEnd();
    glEndList();

    return index;
  }

  void GraphicsOpenGLLegacy::sceneLoad(const std::filesystem::path &filePath)
  {
    std::vector<std::string> fields;
    static Assimp::Importer importer;
    unsigned int flags = aiProcess_Triangulate|aiProcess_SortByPType;
    const aiScene *ai_scene = importer.ReadFile(filePath, flags);

    Field::Scene3D &sceneTemplate = sceneTemplates[filePath];
    for(size_t meshNum = 0; meshNum < ai_scene->mNumMeshes; ++meshNum)
    {
      // Extract vertice data
      sceneTemplate.models.emplace_back();
      Field::Scene3D::Model &model = sceneTemplate.models.back();
      aiMesh &mesh = *ai_scene->mMeshes[meshNum];
      std::vector<glm::vec3> textureCoordinates;
      bool hasTextureCoords = mesh.mTextureCoords[0];
      for(size_t faceNum = 0; faceNum < mesh.mNumFaces; ++faceNum)
      {
        const aiFace &face = mesh.mFaces[faceNum];
        for(size_t i = 0; i < face.mNumIndices; ++i)
        {
          unsigned int index = face.mIndices[i];
          const aiVector3D &vertex = mesh.mVertices[index];
          model.mesh.emplace_back(vertex.x, vertex.y, vertex.z);
          if(hasTextureCoords)
          {
            aiVector3D &coords = mesh.mTextureCoords[0][index];
            model.textureCoordinates.emplace_back(coords.x, 1.f-coords.y, coords.z);
          }
        }
      }

      // Extract texture data
      GLuint textureIndex;
      if(meshNum < ai_scene->mNumTextures)
      {
        model.texture.width = ai_scene->mTextures[meshNum]->mWidth;
        model.texture.height = ai_scene->mTextures[meshNum]->mHeight;
        if(model.texture.height == 0) // compressed
        {
          int width, height, channels;
          unsigned char *imageData = reinterpret_cast<unsigned char *>(ai_scene->mTextures[meshNum]->pcData);
          model.texture.data = stbi_load_from_memory(imageData, model.texture.width, &width, &height, &channels, 0);
          model.texture.width = width;
          model.texture.height = height;
          model.texture.numChannels = channels;
        }
        else // uncompressed
        {
          model.texture.numChannels = 4;
          model.texture.data = new GLubyte[model.texture.height*model.texture.width*4];
          for(size_t y=0; y < model.texture.height; ++y)
          {
            for(size_t x=0; x < model.texture.width; ++x)
            {
              model.texture.data[model.texture.width*y*4+x*4] = ai_scene->mTextures[meshNum]->pcData->r;
              model.texture.data[model.texture.width*y*4+x*4+1] = ai_scene->mTextures[meshNum]->pcData->g;
              model.texture.data[model.texture.width*y*4+x*4+2] = ai_scene->mTextures[meshNum]->pcData->b;
              model.texture.data[model.texture.width*y*4+x*4+3] = ai_scene->mTextures[meshNum]->pcData->a;
            }
          }
        }
        glGenTextures(1, &textureIndex);
        glBindTexture(GL_TEXTURE_2D, textureIndex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, model.texture.width, model.texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, model.texture.data);
        glData[filePath].textures.emplace_back(textureIndex);
      }
      else // No data to extract
      {
        glData[filePath].textures.emplace_back(textureMissingIndex);
        textureIndex = textureMissingIndex;
      }

      glData[filePath].displayLists.emplace_back(generateDisplayList(model, textureIndex));
    }
  }

  void GraphicsOpenGLLegacy::sceneUpdate(const nlohmann::json &message)
  {
    size_t entityId = message["entity_id"].get<size_t>();
    const std::string &sceneName = message["scene_name"];
    components[entityId]->scene = sceneTemplates[sceneName];
    entityToDisplayList[entityId] = glData[sceneName].displayLists[0];
  }

  void GraphicsOpenGLLegacy::update(const nlohmann::json &)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    size_t numComponents = components.size();
    for(size_t entityId=0; entityId < numComponents; ++entityId)
    {
      Component::Graphics3D &component = *components[entityId];
      glPushMatrix();
        glTranslatef(component.position.x, component.position.y, component.position.z);
        glRotatef(component.orientation.x, 1, 0, 0);
        glRotatef(component.orientation.y, 0, 1, 0);
        glRotatef(component.orientation.z, 0, 0, 1);

        glCallList(entityToDisplayList[entityId]);
      glPopMatrix();
    }
    glfwSwapBuffers(window);
    glDisable(GL_TEXTURE_2D);
  }

  void GraphicsOpenGLLegacy::shutdown(const nlohmann::json &)
  {
    glfwTerminate();
  }
}
