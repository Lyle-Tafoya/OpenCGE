#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

#include <OpenCGE/graphics_opengl_legacy.hpp>

namespace OpenCGE
{
  GraphicsOpenGLLegacy::GraphicsOpenGLLegacy(int windowWidth, int windowHeight, const std::string &windowName)
    : System("graphics_3d")
  {
    callbackRegister("scene_update", &GraphicsOpenGLLegacy::sceneUpdate, this);
    callbackRegister("shutdown", &GraphicsOpenGLLegacy::shutdown, this);
    callbackRegister("time_passed", &GraphicsOpenGLLegacy::update, this);

    glfwInit();
    window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    windowResize(width, height);
  }

  void GraphicsOpenGLLegacy::entityAdd(size_t entityId)
  {
    std::unordered_map<std::string, void *> &entity = entities[entityId];

    auto *orientation = static_cast<glm::vec3 *>(entity["orientation"]);
    if(orientation == nullptr)
    {
      orientation = new glm::vec3(0.f, 0.f, 0.f);
      entity["orientation"] = orientation;
    }
    auto *position = static_cast<glm::vec3 *>(entity["position"]);
    if(position == nullptr)
    {
      position = new glm::vec3(0.f, 0.f, 0.f);
      entity["position"] = position;
    }
    auto *scene = static_cast<Field::Scene3D *>(entity["scene_3d"]);
    if(scene == nullptr)
    {
      scene = new Field::Scene3D();
      entity["scene_3d"] = scene;
    }

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

  void GraphicsOpenGLLegacy::sceneLoad(const std::filesystem::path &filePath)
  {

    std::vector<std::string> fields;
    Assimp::Importer importer;
    unsigned int flags = aiProcess_CalcTangentSpace|aiProcess_Triangulate|aiProcess_SortByPType;
    const aiScene *ai_scene = importer.ReadFile(filePath, flags);
    // TODO Store meshes in vertex buffer arrays
    for(size_t mesh_num = 0; mesh_num < ai_scene->mNumMeshes; ++mesh_num)
    {
      aiMesh &mesh = *ai_scene->mMeshes[mesh_num];
      std::vector<glm::vec3> vertices;
      for(size_t vertice_num = 0; vertice_num < mesh.mNumVertices; ++vertice_num)
      {
        aiVector3D &vertice = mesh.mVertices[vertice_num];
        vertices.push_back(glm::vec3(vertice.x, vertice.y, vertice.z));
      }
      sceneTemplates[filePath].meshes.push_back(vertices);
    }
  }

  void GraphicsOpenGLLegacy::scenesLoad(const std::filesystem::path &directoryPath)
  {
    for(auto &directoryEntry : std::filesystem::directory_iterator(directoryPath))
    {
      GraphicsOpenGLLegacy::sceneLoad(directoryEntry.path());
    }
  }

  void GraphicsOpenGLLegacy::sceneUpdate(const nlohmann::json &message)
  {
    size_t entityId = message["entity_id"].get<size_t>();
    components[entityId]->scene = sceneTemplates[message["scene_name"]];
  }

  void GraphicsOpenGLLegacy::update(const nlohmann::json &)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(auto entity : components)
    {
      Component::Graphics3D &component = *entity.second;
      glPushMatrix();
      glTranslatef(component.position.x, component.position.y, component.position.z);
      glRotatef(component.orientation.x, 1, 0, 0);
      glRotatef(component.orientation.y, 0, 1, 0);
      glRotatef(component.orientation.z, 0, 0, 1);

      for(std::vector<glm::vec3> mesh : component.scene.meshes)
      {
        glBegin(GL_TRIANGLES);
        for(glm::vec3 vertice : mesh)
        {
          glColor3f(0.5f, 0.5f, 0.5f);
          glVertex3f(vertice.x, vertice.y, vertice.z);
        }
        glEnd();
      }
      glPopMatrix();
    }
    glfwSwapBuffers(window);
  }

  void GraphicsOpenGLLegacy::shutdown(const nlohmann::json &)
  {
    glfwTerminate();
  }
}
