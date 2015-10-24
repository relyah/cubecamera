#ifndef _SQUAREMODEL_H_
#define _SQUAREMODEL_H_

#include <gdk/gdkkeysyms.h>

#include "Logger.h"
#include "IModel.h"
#include "ICamera.h"
#include "IKeyReleasedListener.h"

class SquareModel: public IModel, public IKeyReleasedListener {

public:
  SquareModel(ICamera *camera, int screenWidth, int screenHeight);
  ~SquareModel();

  virtual glm::mat4 GetModel();
  virtual glm::mat4 GetView();
  virtual glm::mat4 GetProjection();

  bool IsChanged();

  virtual void OnKeyReleased(int key);

private:
  std::stringstream sstm;
  log4cpp::Category* logger;
  ICamera *camera;
  bool isChanged;
  int screenWidth;
  int screenHeight;
  glm::mat4 matrix;
  glm::mat4 projection;
  float xinc, yinc;
  float xpos, ypos;

  void Reset();
};

#endif
