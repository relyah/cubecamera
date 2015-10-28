#include "Square.h"

Square::Square(IOpenGLProgram* program, IModel* model) : AbstractObject(program,model) {
  //logger = Logger::GetLogger();

}

Square::~Square() {
  model=0;
}

void Square::Init() {

  Gen();

  attribute_vp = program->GetAttrib("vp");
  attribute_vn = program->GetAttrib("vn");
  attribute_vc = program->GetAttrib("vc");

  uniform_m = program->GetUniform("model");
  uniform_v = program->GetUniform("view");
  uniform_p = program->GetUniform("projection");

  sstm.str(std::string());
  sstm << "Square attributes vp: " << attribute_vp << ", vn: " << attribute_vn << ", vc: " << attribute_vc << ", uniform m: " << uniform_m  << ", uniform_p: " << uniform_p << std::endl;
  logger->info(sstm.str());


  FillVBO();
  Unbind();
}

void Square::FillVBO() {

  numPoints = 4;
  VertexStructure points[] = {
    0.5f,  0.5f,  0.5f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,
    0.5f, -0.5f,  0.5f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f,

    0.5f,  0.5f,  -0.5f, 0.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,
    0.5f, -0.5f,  -0.5f, 0.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,
    -0.5f, -0.5f,  -0.5f, 0.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,

    -0.5f, -0.5f, 0.5f, -1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f,
    -0.5f, -0.5f,  -0.5f, -1.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f,0.0f,0.0f, 0.0f,1.0f,0.0f

  };

  numIndices = 6;
  unsigned short pointsIndex[] = {
    0,1,2,2,3,0,
    4,6,5,6,4,7,
    8,9,10,10,9,11};

  glGenBuffers(1, &vboPoints);
  glGenBuffers(1, &iboPoints);

  glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
  sstm.str(std::string());
  sstm << "Square vboPoints: " << vboPoints << std::endl;
  logger->info(sstm.str());
  glBufferData(GL_ARRAY_BUFFER, numPoints * sizeof(VertexStructure), points, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPoints);
  sstm.str(std::string());
  sstm << "Square iboPoints: " << iboPoints << std::endl;
  logger->info(sstm.str());
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,numIndices*sizeof(unsigned short), pointsIndex, GL_STATIC_DRAW);

  glEnableVertexAttribArray(attribute_vp);
  glVertexAttribPointer (attribute_vp, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (GLubyte*)NULL);

  glEnableVertexAttribArray(attribute_vn);
  glVertexAttribPointer(attribute_vn, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, normal));

  glEnableVertexAttribArray(attribute_vc);
  glVertexAttribPointer(attribute_vc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, colour));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Square::Render() {
  Bind();

  //logger->info("Square updating...");
  glm::mat4 modelMatrix = model->GetModel();
  glUniformMatrix4fv(uniform_m,1,GL_FALSE,glm::value_ptr(modelMatrix));

  glm::mat4 viewMatrix = model->GetView();
  glUniformMatrix4fv(uniform_v,1,GL_FALSE,glm::value_ptr(viewMatrix));

  glm::mat4 projectionMatrix = model->GetProjection();
  glUniformMatrix4fv(uniform_p,1,GL_FALSE,glm::value_ptr(projectionMatrix));

  sstm.str(std::string());
  sstm << "Square vboPoints: " << vboPoints << std::endl;
  logger->info(sstm.str());
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPoints);
  glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_SHORT,0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  Unbind();
}

void Square::Shutdown() {
  AbstractObject::Shutdown();
  program=0;
  model=0;
}

