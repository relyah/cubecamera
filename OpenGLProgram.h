#ifndef OPENGPROGRAM_H_
#define OPENGLPROGRAM_H_

#include <vector>

#include "AbstractOpenGLProgram.h"
#include "IObject.h"
#include "Camera.h"

using namespace std;

typedef vector<IObject*> TObjects;

class OpenGLProgram : public AbstractOpenGLProgram, public IObject {

public:
  OpenGLProgram(string vsName, string fsName);
  ~OpenGLProgram();

  void AddObject(IObject* object);

  void SetCamera(ICamera *camera);

  void Init();
  void Render();
  void Shutdown();

  virtual void Bind() {}
  virtual void Unbind() {}

  virtual GLuint GetColorTexture() {return 0;}

private:
  string vsName, fsName;
  GLuint vs, fs;
  TObjects objects;
  ICamera *camera;

  void InitProgram();

  void InitObjects();
  void RenderObjects();
  void ShutdownObjects();
};

#endif

