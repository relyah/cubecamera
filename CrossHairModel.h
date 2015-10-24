#ifndef _CROSSHAIRMODEL_H_
#define _CROSSHAIRMODEL_H_

#include "IModel.h"

class CrossHairModel : public IModel {

public:

  virtual bool IsChanged() {return true;}
  virtual glm::mat4 GetModel() {return model;}
  virtual glm::mat4 GetView() {return view;}
  virtual glm::mat4 GetProjection() {return projection;}

private:
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);
};

#endif

