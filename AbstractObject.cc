#include "AbstractObject.h"

AbstractObject::AbstractObject(IOpenGLProgram* program, IModel *model) : program(program), model(model)  {

}

AbstractObject::~AbstractObject() {
  program=0;
  model=0;
}

void AbstractObject::Gen() {
  glGenVertexArrays(1, &vao);
  Bind();
}

void AbstractObject::Bind() {
  glBindVertexArray(vao);
}

void AbstractObject::Unbind() {
  glBindVertexArray(0);
}

void AbstractObject::Shutdown() {
  Unbind();
  glDeleteVertexArrays(1,&vao);
  program = 0;
  model =0;
}
