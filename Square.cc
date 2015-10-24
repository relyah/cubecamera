#include "Square.h"

Square::Square(IOpenGLProgram* program, IModel* model) : AbstractObject(program,model) {
  //logger = Logger::GetLogger();
  points[0] = {    0.5f,  0.5f,  0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};
  points[1] = {  0.5f, -0.5f,  0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};
  points[2] = {   -0.5f, -0.5f,  0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};
  points[3] = {   -0.5f, 0.5f, 0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};

  isHit = false;
  isDrawHit = false;
  hit=NULL;
}

Square::~Square() {
  model=0;

  if (hit!=NULL) {
    delete hit;
    hit=NULL;
  }
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
  sstm << "attributes vp: " << attribute_vp << ", vn: " << attribute_vn << ", vc: " << attribute_vc << ", uniform m: " << uniform_m  << ", uniform_p: " << uniform_p << std::endl;
  logger->info(sstm.str());

  FillVBO();
}

void Square::Gen() {
  AbstractObject::Gen();
  //glGenVertexArrays(1, &vao);
  //glBindVertexArray(vao);
  glGenBuffers(1, &vboPoints);
  //glGenBuffers(1, &vboHit);
}

void Square::FillVBO() {

  unsigned short pointsIndex[] = {0,1,2,2,3,0};

  //glUseProgram(program->GetProgram());
  //program->GenVAO();

  //glGenBuffers(1, &vboPoints);
  glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
  sstm.str(std::string());
  sstm << "vboPoints: " << vboPoints << std::endl;
  logger->info(sstm.str());
  glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexStructure), points, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &iboPoints);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPoints);
  sstm.str(std::string());
  sstm << "iboPoints: " << iboPoints << std::endl;
  logger->info(sstm.str());
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(unsigned short), pointsIndex, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  //std::cout << "vboHit " << vboHit << std::endl;
  //glBindBuffer(GL_ARRAY_BUFFER, vboHit);
  //VertexStructure hitStruct = { 0.0f,0.0f,0.0f, 0.0f,0.0f,1.0f, 1.0f,1.0f,1.0f};
  //glBufferData(GL_ARRAY_BUFFER, 36, NULL, GL_STATIC_DRAW); //&hitStruct
  //glBindBuffer(GL_ARRAY_BUFFER, 0);
  

  glEnableVertexAttribArray(attribute_vp);
  glVertexAttribPointer (attribute_vp, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (GLubyte*)NULL);

  glEnableVertexAttribArray(attribute_vn);
  glVertexAttribPointer(attribute_vn, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, normal));

  glEnableVertexAttribArray(attribute_vc);
  glVertexAttribPointer(attribute_vc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, colour));
}

void Square::Render() {
  Bind();

//  if (model->IsChanged()) {
  //logger->info("Square updating...");
  glm::mat4 modelMatrix = model->GetModel();
  glUniformMatrix4fv(uniform_m,1,GL_FALSE,glm::value_ptr(modelMatrix));

  glm::mat4 viewMatrix = model->GetView();
  glUniformMatrix4fv(uniform_v,1,GL_FALSE,glm::value_ptr(viewMatrix));

  glm::mat4 projectionMatrix = model->GetProjection();
  glUniformMatrix4fv(uniform_p,1,GL_FALSE,glm::value_ptr(projectionMatrix));
//  }

  sstm.str(std::string());
  sstm << "vboPoints: " << vboPoints << std::endl;
  logger->info(sstm.str());
  
  //glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPoints);
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  /*
  if (isDrawHit) {
    glDisable(GL_PROGRAM_POINT_SIZE);glPointSize(40.0f); //use glPointSize from the code 
    glBindBuffer(GL_ARRAY_BUFFER, vboHit);
    glDrawArrays(GL_POINTS,0,1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    }*/
}

void Square::Shutdown() {
  AbstractObject::Shutdown();
  program=0;
  model=0;
}

void Square::Intersect(Ray &ray) {

  glm::mat4 modelMatrix = model->GetModel();
  glm::mat4 view = model->GetView();

  //make plane
  glm::vec4 a =modelMatrix * glm::vec4(points[0].coord3d[0],points[0].coord3d[1],points[0].coord3d[2],1.0f);
  glm::vec4 b = modelMatrix * ( glm::vec4(points[1].coord3d[0],points[1].coord3d[1],points[1].coord3d[2],1.0f));
  glm::vec4 c = modelMatrix * ( glm::vec4(points[2].coord3d[0],points[2].coord3d[1],points[2].coord3d[2],1.0f));
  glm::vec4 d =  modelMatrix * ( glm::vec4(points[3].coord3d[0],points[3].coord3d[1],points[3].coord3d[2],1.0f));

  Plane p("test",a,b,c,d);

//test for intersection
  if (p.Intersect(ray, hit)) {
    isHit = true;
    logger->info("hit");
    SetColour(0.0f,0.0f,1.0f);

    if (hit==NULL) {
      logger->info("hit is null.");
    }
  } else if (isHit){
    isHit=false;
    SetColour(1.0f,0.0f,0.0f);
  }  /*if (hit!=NULL) {
    glm::mat4 invMM = glm::inverse(modelMatrix);
    *hit = invMM * (*hit); 
    isDrawHit = true;
    SetupHit();
  }*/

}

void Square::SetColour(float red, float green, float blue) {
  for (int i=0; i <4; i++) {
    points[i].colour[0]=red;
    points[i].colour[1]=green;
    points[i].colour[2]=blue;
  }

  Bind();
  glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
  float *buf = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

  if (buf==NULL) {
    logger->info("setColour glMapBuffer failed.");
  } else {
    memcpy(buf, points, 4*sizeof(VertexStructure));
  }

  glUnmapBuffer(GL_ARRAY_BUFFER);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Square::SetupHit() {
  return;

  Bind();
  glBindBuffer(GL_ARRAY_BUFFER, vboHit);
  float *buf = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

  if (buf==NULL) {
    logger->info("setuphit glMapBuffer failed.");
  } else {
    VertexStructure hitStruct = { hit->x, hit->y, hit->z, 0.0f,0.0f,1.0f, 1.0f,1.0f,1.0f};
    std::cout << "hit x: " << hit->x << ", y: " << hit->y << ", z: " <<  hit->z << std::endl;
    memcpy(buf, &hitStruct, sizeof(VertexStructure));
  }

  glUnmapBuffer(GL_ARRAY_BUFFER);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
