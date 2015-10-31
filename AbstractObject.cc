#include "AbstractObject.h"

AbstractObject::AbstractObject(IOpenGLProgram* program, IModel *model, bool isRenderToFBO) :
  program(program),
  model(model),
  isRenderToFBO(isRenderToFBO){

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
  std::cout << "Binding VAO: " << vao << std::endl;
  glBindVertexArray(vao);
}

void AbstractObject::Unbind() {
  std::cout << "UnBinding VAO: " << vao << std::endl;
  glBindVertexArray(0);
}

void AbstractObject::Shutdown() {
  Unbind();
  glDeleteVertexArrays(1,&vao);
  program = 0;
  model =0;
}
