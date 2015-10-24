#ifndef OPENGPROGRAM_H_
#define OPENGLPROGRAM_H_

#include <vector>

#include "AbstractOpenGLProgram.h"
#include "IObject.h"
#include "Camera.h"

typedef std::vector<IObject*> TObjects;

class OpenGLProgram : public AbstractOpenGLProgram {

public:
  OpenGLProgram();
  ~OpenGLProgram();

  void AddObject(IObject* object);

  void SetCamera(Camera* camera);

  void Init();
  void Render();
  void Shutdown();

private:
  //GLuint vao, vbo;
  GLuint vs, fs;
  TObjects objects;
  Camera* camera;

  void InitProgram();

  void InitObjects();
  void RenderObjects();
  void ShutdownObjects();
};

#endif

