#ifndef _TELEVISION_H_
#define _TELEVISION_H_

#include "Logger.h"
#include "DataStructures.h"
#include "IObject.h"
#include "AbstractObject.h"
#include "IOpenGLProgram.h"
#include "IModel.h"

class Television : public AbstractObject {

public:
  Television(IOpenGLProgram *program, IModel *model, IObject *source);
  ~Television();

  void Init();
  void Render();
  virtual void Shutdown();

private:
  IObject *source;

  GLuint vboPoints;
  GLuint iboPoints;
  GLuint attribute_vp, attribute_vt;
  GLint uniform_m;
  GLint uniform_v;
  GLint uniform_p;
  int numPoints, numIndices;

  GLuint color_texture;

  void FillVBO();
};

#endif
