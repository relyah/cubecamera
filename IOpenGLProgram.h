#ifndef _IOPENGLPROGRAM_H_
#define _IOPENGLPROGRAM_H_

#include <epoxy/gl.h>

class IOpenGLProgram {

public:
  virtual ~IOpenGLProgram() {}

  virtual void Use() =0;
  virtual GLuint GetProgram() = 0;
  virtual GLint GetAttrib(const char *name) = 0;
  virtual GLint GetUniform(const char *name) = 0;

  //virtual void GenVAO() = 0;

  virtual void Init() = 0;
  virtual void Render() = 0;
  virtual void Shutdown() =0;
};

#endif
