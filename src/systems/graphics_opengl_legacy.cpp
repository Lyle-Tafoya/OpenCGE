#include <OpenCGE/graphics_opengl_legacy.hpp>

#include <assimp/postprocess.h>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/filesystem.hpp>

namespace OpenCGE
{

  GraphicsOpenGLLegacy::GraphicsOpenGLLegacy()
  {
    componentRegister("orientation", &createPoint3D);
    componentRegister("position", &createPoint3D);
    componentRegister("scene_3d", &createScene3D);
    callbackRegister("scene_update", &GraphicsOpenGLLegacy::sceneUpdate, this);
    callbackRegister("shutdown", &GraphicsOpenGLLegacy::shutdown, this);
    callbackRegister("time_passed", &GraphicsOpenGLLegacy::update, this);

    glfwInit();
    window = glfwCreateWindow(640, 480, "OpenCGE", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    windowResize(width, height);
  }

  void * GraphicsOpenGLLegacy::createPoint3D()
  {
    return new Components::Point3D();
  }

  void * GraphicsOpenGLLegacy::createScene3D()
  {
    return new Components::Scene3D();
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

    scene_templates[scene_name] = importer.ReadFile(file_path, aiProcess_CalcTangentSpace|aiProcess_Triangulate|aiProcess_SortByPType);
  }

  void GraphicsOpenGLLegacy::scenesLoad(std::string const& directory_path)
  {
    boost::filesystem::path entity_directory(directory_path);
    for(auto &dir_entry : boost::make_iterator_range(boost::filesystem::directory_iterator(entity_directory), {}))
    {
      GraphicsOpenGLLegacy::sceneLoad(dir_entry.path().string());
    }
  }

  void GraphicsOpenGLLegacy::sceneUpdate(untyped_map & message)
  {
    int &entity_id = *(int *)message["entity_id"];
    untyped_map &components = entities[entity_id];
    auto &scene_3d = *(Components::Scene3D *)components["scene_3d"];
    if(scene_3d.scene_data == nullptr)
    {
      scene_3d.scene_data = new aiScene();
    }
    auto &scene_name = *(std::string *)message["scene_name"];

    *scene_3d.scene_data = *scene_templates[scene_name];
  }

  void GraphicsOpenGLLegacy::update(untyped_map &)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(auto entity : entities)
    {
      untyped_map &components = entity.second;
      glPushMatrix();
      auto &position = *(Components::Point3D *)components["position"];
      glTranslatef(position.x, position.y, position.z);
      auto &orientation = *(Components::Point3D *)components["orientation"];
      glRotatef(orientation.x, 1, 0, 0);
      glRotatef(orientation.y, 0, 1, 0);
      glRotatef(orientation.z, 0, 0, 1);

      auto &scene_3d = *(Components::Scene3D *)components["scene_3d"];

      for(size_t mesh_num = 0; mesh_num < scene_3d.scene_data->mNumMeshes; ++mesh_num)
      {
        aiMesh &mesh = *scene_3d.scene_data->mMeshes[mesh_num];
        glBegin(GL_TRIANGLES);
        for(size_t vertice_num = 0; vertice_num < mesh.mNumVertices; ++vertice_num)
        {
          aiVector3D &vertice = mesh.mVertices[vertice_num];
          glColor3f(0.5f, 0.5f, 0.5f);
          glVertex3f(vertice.x, vertice.y, vertice.z);
        }
        glEnd();
      }
      glPopMatrix();
    }
    glfwSwapBuffers(window);
  }

  void GraphicsOpenGLLegacy::shutdown(untyped_map &)
  {
    glfwTerminate();
    for(auto entry : scene_templates)
    {
      delete entry.second;
    }
  }
}
