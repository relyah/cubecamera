#ifndef _ABSTRACTCAMERA_H_
#define _ABSTRACTCAMERA_H_

#include "ICamera.h"

class AbstractCamera : public ICamera {

public:
  AbstractCamera();
  virtual ~AbstractCamera();

  virtual bool IsChanged();
  virtual glm::mat4 GetModel();
  virtual glm::mat4 GetView();
  virtual glm::mat4 GetProjection();
  virtual glm::vec3 GetPosition() = 0;
  virtual void Update(glm::vec3 &eye, glm::vec3 &lookAt, glm::vec3 &up) = 0;

protected:
  bool isChanged;
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 projection;


};
#endif
