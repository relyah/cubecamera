#ifndef _CAMERABASIC_H_
#define _CAMERABASIC_H_

#include "ICamera.h"

class CameraBasic : public ICamera {

public:
CameraBasic(int screenWidth, int screenHeight) :
  screenWidth(screenWidth), screenHeight(screenHeight) {}

  virtual ~CameraBasic() {}

  virtual void Init() {}
  virtual void Render() {}
  virtual void Shutdown() {}

  virtual int GetScreenWidth() {return screenWidth;}
  virtual int GetScreenHeight() {return screenHeight;}
  virtual glm::vec3 GetPosition() {return glm::vec3(1.0f);}
  virtual void Update(glm::vec3 &eye, glm::vec3 &lookAt, glm::vec3 &up) {
    eye = glm::vec3(0.0f);
    lookAt = glm::vec3(0.0f);
    up = glm::vec3(0.0f);
  }

  virtual bool IsChanged() {return false;}
  virtual glm::mat4 GetModel() {return glm::mat4(1.0f);}
  virtual glm::mat4 GetView() {return glm::mat4(1.0f);}
  virtual glm::mat4 GetProjection() {return glm::mat4(1.0f);}

private:
  int screenWidth;
  int screenHeight;
};

#endif
