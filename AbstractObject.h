#ifndef _ABSTRACTOBJECT_H_
#define _ABSTRACTOBJECT_H_

#include "IObject.h"
#include "AdminBase.h"
#include "IOpenGLProgram.h"
#include "IModel.h"

class AbstractObject : public AdminBase, public IObject {

public:
  AbstractObject(IOpenGLProgram *program, IModel *model, bool isRenderToFBO=false);
  virtual ~AbstractObject();

  virtual void Shutdown();

  virtual void Bind();
  virtual void Unbind();

  virtual GLuint GetColorTexture() {return color_texture;}

protected:
  IOpenGLProgram *program;
  IModel *model;
  GLuint vao;

  bool isRenderToFBO;
  GLuint fbo;
  GLuint color_texture;
  GLuint depth_texture;

  virtual void Gen();
};

#endif
