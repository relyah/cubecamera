#include "Camera.h"

#define PI 3.14159265

Camera::Camera(IOpenGLProgram *program, int screenWidth, int screenHeight)
  : AbstractObject(program,this), screenWidth(screenWidth), screenHeight(screenHeight){
  logger = Logger::GetLogger();

  Reset();
}

Camera::~Camera() {
  program=0;
  logger = 0;
}

int Camera::GetScreenWidth() {
  return screenWidth;
}

int Camera::GetScreenHeight() {
  return screenHeight;
}

glm::vec3 Camera::GetPosition() {
  return cameraPosition;
}

void Camera::Init() {
/*  Gen();
  isChanged = true;

  GLuint attribute_vp = program->GetAttrib("vp");
  GLuint attribute_vn = program->GetAttrib("vn");
  GLuint attribute_vc = program->GetAttrib("vc");

  VertexStructure points[] = {
    cameraPosition.x, cameraPosition.y, cameraPosition.z, 1.0f,0.0f,0.0f, 1.0f,1.0f,1.0f,
    cameraLookAt.x, cameraLookAt.y, cameraLookAt.z, 1.0f,0.0f,0.0f, 1.0f,1.0f,1.0f
  };

  sstm.str(std::string());
  sstm << "camera vboPoints: " << vboPoints << std::endl;
  logger->info(sstm.str());
  glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
  glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(VertexStructure), points, GL_STATIC_DRAW);

  glEnableVertexAttribArray(attribute_vp);
  glVertexAttribPointer (attribute_vp, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (GLubyte*)NULL);

  glEnableVertexAttribArray(attribute_vn);
  glVertexAttribPointer(attribute_vn, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, normal));

  glEnableVertexAttribArray(attribute_vc);
  glVertexAttribPointer(attribute_vc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure),(GLvoid*)offsetof(struct VertexStructure, colour));

  uniform_m = program->GetUniform("model");
  uniform_v = program->GetUniform("view");
  uniform_p = program->GetUniform("projection");

  sstm.str(std::string());
  sstm << "uniform v: " << uniform_v << ", p: " << uniform_p << std::endl;
  logger->info(sstm.str());

  Unbind();*/
}

void Camera::Gen() {
  AbstractObject::Gen();
  glGenBuffers(1,&vboPoints);
}

void Camera::Render() {
  /*if (isChanged) {
    Bind();
    isChanged = false;

    glm::mat4 model =  this->GetModel();
    glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(model));

    //view = glm::lookAt(cameraPosition, cameraLookAt, cameraUp);
    glUniformMatrix4fv(uniform_v, 1, GL_FALSE, glm::value_ptr(view));

    glUniformMatrix4fv(uniform_p, 1, GL_FALSE, glm::value_ptr(projection));

    if (isCameraMoving) {
      RenderRay();
    }

    Unbind();

  }*/
}

void Camera::Shutdown() {
  AbstractObject::Shutdown();
  program=0;
  glDeleteBuffers(1,&vboPoints);
}

void Camera::Update(glm::vec3 &eye, glm::vec3 &lookAt, glm::vec3 &up) {
  logger->info("camera updating view...");

  cameraPosition = glm::vec3(eye);
  cameraLookAt = glm::vec3(lookAt);
  cameraUp = glm::vec3(up);

  BuildView();

  isChanged = true;
}

void Camera::OnScroll(GdkScrollDirection dir) {
  if (dir==GDK_SCROLL_UP) {
    zoomDelta += 0.1f;
  } else if (dir==GDK_SCROLL_DOWN) {
    zoomDelta += -0.1f;
  } else {
    return;
  }

  cameraPosition = cameraOrigPos;
  ZoomCamera();

  isChanged = true;
}

void Camera::OnDrag(double x, double y) {
  if (isCameraMoving) {

    glm::vec2 delta = (glm::vec2(x,y) - cursor);

    cameraRotate += glm::vec2(0.1f*delta.x, 0.1f*delta.y);

    ZoomCamera();

    cursor = glm::vec2(x,y);
    isChanged = true;
  }
}

void Camera::OnButtonPressed(int button, double x, double y) {
  isCameraMoving =  button==1;
  if(isCameraMoving) {
    //logger->info("camera moving...");
    cursor = glm::vec2(x,y);
  }
}

void Camera::OnButtonReleased(int button, double x, double y) {
  isCameraMoving = !(button==1);
  //logger->info("released");
}

void Camera::OnKeyReleased(int key) {
  switch (key) {
  case GDK_KEY_r:
    Reset();
    break;
  }
}

void Camera::ZoomCamera() {

  glm::mat4 rotX = glm::mat4(1.0f);
  glm::mat4 rotY = glm::mat4(1.0f);
  float radX = glm::radians(cameraRotate.y);
  float radY = glm::radians(cameraRotate.x);

  //sstm.str(std::string());
  //sstm << "rad: " << rad << std::endl;
  //logger->info(sstm.str());

  //sstm << "rad: " << rad  << std::endl;
  //logger->info(sstm.str());
  rotX = glm::rotate(rotX,radX,glm::vec3(1.0f,0.0,0.0));
  rotY = glm::rotate(rotY,radY,glm::vec3(0.0,1.0f,0.0));
  cameraPosition = glm::vec3(rotY * rotX * glm::vec4(cameraOrigPos,1.0f));

  glm::vec3 d = zoomDelta*glm::normalize(cameraLookAt - cameraPosition);
  cameraPosition = cameraPosition +  d;

  view = glm::lookAt(cameraPosition, cameraLookAt, cameraUp);

  sstm.str(std::string());
  sstm << "zoomDelta: " << zoomDelta << " d: "<< d.x << "," << d.y << std::endl;
  logger->info(sstm.str());
}

void Camera::Reset() {

  zoomDelta = 0.0f;

  cameraPosition = cameraOrigPos = glm::vec3(0.0, 0.0, 5.0);  // the position of your camera, in world space
  cameraLookAt = glm::vec3(0.0, 0.0, 0.0);  // where you want to look at, in world space
	cameraUp = glm::vec3(0.0, 1.0, 0.0); //up direction; probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
	//cameraRight = glm::vec3(1.0, 0.0, 0.0);

  cameraRotate = glm::vec2(0.0f, 0.0f);

  BuildView();

  BuildPerspective();

  isChanged = true;
}

void Camera::BuildView() {
  //view = glm::lookAt(cameraPosition, cameraLookAt, cameraUp);

  glm::vec3 look = cameraLookAt - cameraPosition;
  glm::vec3 w = -glm::normalize(look);

  glm::vec3 v = glm::normalize(cameraUp - glm::dot(cameraUp,w)*w);

  glm::vec3 u = glm::cross(v,w);

  glm::mat4 t = glm::mat4(1.0f);
  t[3][0] = -cameraPosition[0];
  t[3][1] = -cameraPosition[1];
  t[3][2] = -cameraPosition[2];
  t[3][3] = 1.0;

  glm::mat4 r;
  r[0][0] = u[0]; r[1][0]= u[1]; r[2][0]=u[2]; r[3][0]=0.0f;
  r[0][1] = v[0]; r[1][1]= v[1]; r[2][1]=v[2]; r[3][1]=0.0f;
  r[0][2] = w[0]; r[1][2]= w[1]; r[2][2]=w[2]; r[3][2]=0.0f;
  r[0][3] = 0.0f; r[1][3]= 0.0f; r[2][3]=0.0f; r[3][3]=1.0f;

  view = t*r;
}

void Camera::BuildPerspective() {
  //projection =  glm::perspective(45.0f, 1.0f * screenWidth / screenHeight, 0.1f, 100.0f); //glm::mat4(1.0f);//

  float fovdeg = 15.0f;
  float aspect = screenWidth / screenHeight;
  float f = cotan(0.5 * fovdeg * PI / 180.0);
  float near = -0.1f;
  float far = -100.0f;
  float fn = (far+near)/(near-far);

  projection[0][0] = f/aspect; projection[1][0] = 0.0; projection[2][0] = 0.0; projection[3][0] = 0.0;
  projection[0][1] = 0.0; projection[1][1] = f; projection[2][1] = 0.0; projection[3][1] = 0.0;
  projection[0][2] = 0.0; projection[1][2] = 0.0; projection[2][2] = fn; projection[3][2] = 2.0*fn;
  projection[0][3] = 0.0; projection[1][3] = 0.0; projection[2][3] = -1.0; projection[3][3] = 0.0;
}

double Camera::cotan(double i) { return(1 / tan(i)); }

void Camera::RenderRay() {
  //glBindBuffer(GL_ARRAY_BUFFER, vboPoints);
  glDrawArrays(GL_LINES,0,2);
  //glBindBuffer(GL_ARRAY_BUFFER,0);
}
