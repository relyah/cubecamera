#ifndef _ICAMERA_H_
#define _ICAMERA_H_

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IModel.h"

class ICamera : public IModel {

public:
  virtual ~ICamera() {};

  virtual int GetScreenWidth() = 0;
  virtual int GetScreenHeight() = 0;
  virtual glm::vec3 GetPosition() = 0;
  virtual void Update(glm::vec3 &eye, glm::vec3 &lookAt, glm::vec3 &up) = 0;
};
#endif
