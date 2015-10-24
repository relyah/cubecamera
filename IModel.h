#ifndef _IMODEL_H_
#define _IMODEL_H_

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class IModel {

public:

  virtual ~IModel() {}

  virtual bool IsChanged() = 0;
  virtual glm::mat4 GetModel() = 0;
  virtual glm::mat4 GetView() = 0;
  virtual glm::mat4 GetProjection() = 0;
};

#endif
