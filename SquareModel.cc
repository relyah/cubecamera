#include "SquareModel.h"

SquareModel::SquareModel(ICamera* camera, int screenWidth, int screenHeight) : camera(camera), screenWidth(screenWidth), screenHeight(screenHeight) {
  logger = Logger::GetLogger();
  isChanged = true;
  Reset();
}

SquareModel::~SquareModel() {
  logger = 0;
}

bool SquareModel::IsChanged() {
  return isChanged;
}

glm::mat4 SquareModel::GetModel() {

  if (isChanged) {
    //logger->info("square model updated");
    matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos,ypos,0.0f));
    isChanged = false;
  }

  return matrix;
}

glm::mat4 SquareModel::GetView() {
  return camera->GetView();
}


glm::mat4 SquareModel::GetProjection() {
  return camera->GetProjection();// projection;
}

void SquareModel::OnKeyReleased(int key) {
  //sstm.str(std::string());
  //sstm << "got key in SquareModel " << key << " " << GDK_KEY_KP_Left <<  std::endl;
  //logger->info(sstm.str());
  switch (key) {
  case GDK_KEY_Left:
  case GDK_KEY_KP_Left:
    //logger->info("left");
    xpos -= xinc;
    isChanged = true;
    break;
  case GDK_KEY_Up:
  case GDK_KEY_KP_Up:
    ypos += yinc;
    isChanged = true;
    break;
  case GDK_KEY_Right:
  case GDK_KEY_KP_Right: 
    xpos += xinc;
    isChanged = true;
    break;
  case GDK_KEY_Down:
  case GDK_KEY_KP_Down:
    ypos -= yinc;
    isChanged = true;
    break;
  case GDK_KEY_r:
    Reset();
    isChanged = true;
    break;
  default: break;

  }
}

void SquareModel::Reset() {
  projection =  glm::perspective(45.0f, 1.0f * screenWidth / screenHeight, 0.1f, 100.0f);
    
  xinc = 0.1f; yinc=0.1f;
  xpos = 0.0f; ypos=0.0f;

  isChanged = true;
}
