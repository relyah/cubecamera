#ifndef _ABSTRACTOBJECT_H_
#define _ABSTRACTOBJECT_H_

#include <epoxy/gl.h>
#include "IObject.h"
#include "AdminBase.h"
#include "IOpenGLProgram.h"
#include "IModel.h"

class AbstractObject : public AdminBase, public IObject {

public:
  AbstractObject(IOpenGLProgram *program, IModel *model);
  virtual ~AbstractObject();

  virtual void Shutdown();

protected:
  IOpenGLProgram *program;
  IModel *model;
  GLuint vao;

  virtual void Gen();
  virtual void Bind();

};

#endif
