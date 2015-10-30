#include "OpenGLProgram.h"

OpenGLProgram::OpenGLProgram(string vsName, string fsName) : vsName(vsName), fsName(fsName) {
  logger->info("Starting OpenGLProgram...");

  objects = TObjects();
}

OpenGLProgram::~OpenGLProgram() {
  logger->info("Stopped OpenGLProgram.");
}

void OpenGLProgram::AddObject(IObject* object) {
  objects.push_back(object);
}

void OpenGLProgram::SetCamera(ICamera* camera) {
  this->camera = camera;
}

void OpenGLProgram::Init() {
  logger->info("Init OpenGLProgram...");

  InitProgram();

  camera->Init();
  InitObjects();
}

void OpenGLProgram::InitObjects() {
  if (objects.size()==0) {return;}

  for (TObjects::iterator it = objects.begin() ; it != objects.end(); ++it) {
    (*it)->Init();
  }
}

void OpenGLProgram::Render() {

  //logger->info("Program rendering...");

  Use();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.1, 0.0, 1.0);
  glPointSize(40.0f);

  camera->Render();
  RenderObjects();

  glBindVertexArray (0);
  glUseProgram (0);

  glFlush();
}

void OpenGLProgram::RenderObjects() {
  if (objects.size()==0) {return;}

  for (TObjects::iterator it = objects.begin() ; it != objects.end(); ++it) {
    (*it)->Render();
  }
}

void OpenGLProgram::Shutdown() {

  camera->Shutdown();
  camera=0;

  ShutdownObjects();

  glUseProgram(0);

  glDetachShader(GetProgram(), vs);
  glDetachShader(GetProgram(), fs);

  glDeleteShader(fs);
  glDeleteShader(vs);

  objects.clear();

  AbstractOpenGLProgram::Shutdown();//  glDeleteProgram(GetProgram());
}

void OpenGLProgram::ShutdownObjects() {
  if (objects.size()==0) {return;}

  for (TObjects::iterator it = objects.begin() ; it != objects.end(); ++it) {
    (*it)->Shutdown();
  }

  objects.clear();
}

void OpenGLProgram::InitProgram() {

  CreateProgram(vsName.c_str(), fsName.c_str(),vs,fs);//"cube.vs.glsl","cube.fs.glsl",vs,fs);

  sstm.str(std::string());
  sstm << "program: " << program << std::endl;
  logger->info(sstm.str());
}

