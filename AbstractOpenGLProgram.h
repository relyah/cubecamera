#ifndef _ABSTRACTOPENGLPROGRAM_H_
#define _ABSTRACTOPENGLPROGRAM_H_

#include "IOpenGLProgram.h"
#include "AdminBase.h"

class AbstractOpenGLProgram :public IOpenGLProgram,  public AdminBase {

public:
  virtual void Use();
  //virtual void GenVAO();
  virtual void Shutdown();

protected:
  GLuint program;

  GLuint CreateProgram(const char *vertexfile, const char *fragmentfile, GLuint &vshader, GLuint &fshader);
  GLuint CreateShader(GLenum type, const char *filename);

  GLuint GetProgram() {return program;}

  GLint GetAttrib(const char *name);
  GLint GetUniform(const char *name);
private:
  GLint GetAttrib(GLuint program, const char *name);
  GLint GetUniform(GLuint program, const char *name);
  char* file_read(const char* filename);
  void print_log(GLuint object);
};

#endif
