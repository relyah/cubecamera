#include "CrossHair.h"

CrossHair::CrossHair(IOpenGLProgram *program, IModel *model) : AbstractObject(program,model) {

}

CrossHair::~CrossHair() {

}

void CrossHair::Init() {
  Gen();
  glGenBuffers(1, &vboPoints);

  attribute_vp = program->GetAttrib("vp");
  attribute_vn = program->GetAttrib("vn");
  attribute_vc = program->GetAttrib("vc");

  uniform_m = program->GetUniform("model");
  uniform_v = program->GetUniform("view");
  uniform_p = program->GetUniform("projection");

  VertexStructure globalAxis[] = {
    0.0f,-1.0f,0.0f, 0.0f,0.0f,1.0f, 1.0f,1.0f,1.0f,
    0.0f,1.0f,0.0f, 0.0f,0.0f,1.0f, 1.0f,1.0f,1.0f,
    -1.0f,0.0f,0.0f, 0.0f,0.0f,1.0f, 1.0f,1.0f,1.0f,
    1.0f,0.0f,0.0f,  0.0f,0.0f,1.0f, 1.0f,1.0f,1.0f
  };

  glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
  glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexStructure), globalAxis, GL_STATIC_DRAW);

  glEnableVertexAttribArray(attribute_vp);
  glVertexAttribPointer (attribute_vp, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (GLubyte*)NULL);

  glEnableVertexAttribArray(attribute_vn);
  glVertexAttribPointer(attribute_vn, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, normal));

  glEnableVertexAttribArray(attribute_vc);
  glVertexAttribPointer(attribute_vc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, colour));

  glBindBuffer(GL_ARRAY_BUFFER,0);

  Unbind();
}

void CrossHair::Render() {
  Bind();
  glm::mat4 modelMatrix = model->GetModel();
  glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(modelMatrix));

  glm::mat4 view = model->GetView();
  glUniformMatrix4fv(uniform_v, 1, GL_FALSE, glm::value_ptr(view));

  glm::mat4 projection = model->GetProjection();
  glUniformMatrix4fv(uniform_p, 1, GL_FALSE, glm::value_ptr(projection));

  //glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
  glDrawArrays(GL_LINES,0,4);
  //glBindBuffer(GL_ARRAY_BUFFER,0);

  Unbind();
}

void CrossHair::Shutdown() {
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glDeleteBuffers(1,&vboPoints);
}
