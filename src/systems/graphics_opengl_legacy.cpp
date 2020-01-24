#include <filesystem>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    windowResize(width, height);
  }

  void GraphicsOpenGLLegacy::entityAdd(size_t entityId)
  {
    Entity &entity = entities[entityId];
    if(entityToDisplayList.size() <= entityId) { entityToDisplayList.resize(entityId+1); }

    auto *orientation = ensureFieldExists<glm::vec3>(entity, "orientation");
    auto *position = ensureFieldExists<glm::vec3>(entity, "position");
    auto *scene = ensureFieldExists<Field::Scene3D>(entity, "scene_3d");

    components[entityId] = new Component::Graphics3D(*orientation, *position, *scene);
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

  GLuint GraphicsOpenGLLegacy::generateDisplayList(const std::vector<glm::vec3> &mesh)
  {
    GLuint index = glGenLists(1);
    glNewList(index, GL_COMPILE);
      glBegin(GL_TRIANGLES);
        size_t numVertices = mesh.size();
        for(size_t v = 0; v < numVertices; v += 3)
        {
          glVertex3f(mesh[v].x, mesh[v].y, mesh[v].z);
          glVertex3f(mesh[v+1].x, mesh[v+1].y, mesh[v+1].z);
          glVertex3f(mesh[v+2].x, mesh[v+2].y, mesh[v+2].z);
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
    for(size_t mesh_num = 0; mesh_num < ai_scene->mNumMeshes; ++mesh_num)
    {
      aiMesh &mesh = *ai_scene->mMeshes[mesh_num];
      std::vector<glm::vec3> vertices;
      for(size_t faceNum = 0; faceNum < mesh.mNumFaces; ++faceNum)
      {
        aiFace face = mesh.mFaces[faceNum];
        aiVector3D &vertex = mesh.mVertices[face.mIndices[0]];
        vertices.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
        vertex = mesh.mVertices[face.mIndices[1]];
        vertices.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
        vertex = mesh.mVertices[face.mIndices[2]];
        vertices.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
      }
      sceneTemplates[filePath].meshes.push_back(vertices);
      sceneTemplates[filePath].displayListIndex = generateDisplayList(vertices);
    }
  }

  void GraphicsOpenGLLegacy::sceneUpdate(const nlohmann::json &message)
  {
    size_t entityId = message["entity_id"].get<size_t>();
    const std::string &sceneName = message["scene_name"];
    components[entityId]->scene = sceneTemplates[sceneName];
    entityToDisplayList[entityId] = sceneTemplates[sceneName].displayListIndex;
  }

  void GraphicsOpenGLLegacy::update(const nlohmann::json &)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    size_t seed = 0;
    for(size_t entityId=0; entityId < components.size(); ++entityId)
    {
      Component::Graphics3D &component = *components[entityId];
      glColor3f(0.5f, 0.5f, 0.5f);
      glPushMatrix();
        glTranslatef(component.position.x, component.position.y, component.position.z);
        glRotatef(component.orientation.x, 1, 0, 0);
        glRotatef(component.orientation.y, 0, 1, 0);
        glRotatef(component.orientation.z, 0, 0, 1);

        glCallList(entityToDisplayList[entityId]);
      glPopMatrix();
    }
    glfwSwapBuffers(window);
  }

  void GraphicsOpenGLLegacy::shutdown(const nlohmann::json &)
  {
    glfwTerminate();
  }
}
