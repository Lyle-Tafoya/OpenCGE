#include <OpenCGE/graphics_opengl_legacy.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/filesystem.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace OpenCGE
{

  GraphicsOpenGLLegacy::GraphicsOpenGLLegacy(int window_width, int window_height, std::string const& window_name)
    : System("graphics_3d")
  {
    callbackRegister("scene_update", &GraphicsOpenGLLegacy::sceneUpdate, this);
    callbackRegister("shutdown", &GraphicsOpenGLLegacy::shutdown, this);
    callbackRegister("time_passed", &GraphicsOpenGLLegacy::update, this);

    glfwInit();
    window = glfwCreateWindow(window_width, window_height, window_name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    windowResize(width, height);
  }

  void GraphicsOpenGLLegacy::entityAdd(size_t entity_id)
  {
    std::unordered_map<std::string, void *> &entity = entities[entity_id];

    auto *orientation = (Field::Point3D *)entity["orientation"];
    if(orientation == nullptr)
    {
      orientation = new Field::Point3D(0.f, 0.f, 0.f);
      entity["orientation"] = orientation;
    }
    auto *position = (Field::Point3D *)entity["position"];
    if(position == nullptr)
    {
      position = new Field::Point3D(0.f, 0.f, 0.f);
      entity["position"] = position;
    }
    auto *scene = (Field::Scene3D *)entity["scene_3d"];
    if(scene == nullptr)
    {
      scene = new Field::Scene3D();
      entity["scene_3d"] = scene;
    }

    components[entity_id] = new Component::Graphics3D(*orientation, *position, *scene);
  }

  void GraphicsOpenGLLegacy::entityRemove(size_t entity_id)
  {
    delete components[entity_id];
    components.erase(entity_id);
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

  void GraphicsOpenGLLegacy::sceneLoad(std::string const& file_path)
  {

    std::vector<std::string> fields;
    boost::split_regex(fields, file_path, boost::regex("\\.dae"));
    std::string scene_name = fields.front();
    split(fields, scene_name, boost::is_any_of("/"));
    scene_name = fields.back();
    Assimp::Importer importer;
    unsigned int flags = aiProcess_CalcTangentSpace|aiProcess_Triangulate|aiProcess_SortByPType;
    const aiScene *ai_scene = importer.ReadFile(file_path, flags);
    // TODO Store meshes in vertex buffer arrays
    for(size_t mesh_num = 0; mesh_num < ai_scene->mNumMeshes; ++mesh_num)
    {
      aiMesh &mesh = *ai_scene->mMeshes[mesh_num];
      std::vector<Field::Point3D> vertices;
      for(size_t vertice_num = 0; vertice_num < mesh.mNumVertices; ++vertice_num)
      {
        aiVector3D &vertice = mesh.mVertices[vertice_num];
        vertices.push_back(Field::Point3D(vertice.x, vertice.y, vertice.z));
      }
      scene_templates[scene_name].meshes.push_back(vertices);
    }
  }

  void GraphicsOpenGLLegacy::scenesLoad(std::string const& directory_path)
  {
    boost::filesystem::path entity_directory(directory_path);
    for(auto &dir_entry : boost::make_iterator_range(boost::filesystem::directory_iterator(entity_directory), {}))
    {
      GraphicsOpenGLLegacy::sceneLoad(dir_entry.path().string());
    }
  }

  void GraphicsOpenGLLegacy::sceneUpdate(nlohmann::json const& message)
  {
    size_t entity_id = message["entity_id"];
    components[entity_id]->scene = scene_templates[message["scene_name"]];
  }

  void GraphicsOpenGLLegacy::update(nlohmann::json const&)
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

      for(std::vector<Field::Point3D> mesh : component.scene.meshes)
      {
        glBegin(GL_TRIANGLES);
        for(Field::Point3D vertice : mesh)
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

  void GraphicsOpenGLLegacy::shutdown(nlohmann::json const&)
  {
    glfwTerminate();
  }
}
