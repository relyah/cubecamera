#ifndef _OPENGLAPPLICATION_H_
#define _OPENGLAPPLICATION_H_

#include "AdminBase.h"
#include "OpenGLManager.h"
#include "OpenGLProgram.h"
#include "IObject.h"
#include "Square.h"
#include "CrossHairModel.h"
#include "CrossHair.h"
#include "IModel.h"
#include "SquareModel.h"
#include "Camera.h"
#include "InputManager.h"
#include "Television.h"
#include "CameraBasic.h"

using namespace std;

class OpenGLApplication : public AdminBase, public IKeyReleasedListener, public IScrollListener, public IDragListener, IButtonPressedListener, IButtonReleasedListener {
public:
  OpenGLApplication(int screenWidth, int screenHeight);
  virtual ~OpenGLApplication();

  void Init();
  void Render();
  void Shutdown();

  void OnKeyReleased(int key);
  void OnScroll(GdkScrollDirection dir);
  void OnDrag(double x, double y);
  void OnButtonPressed(int button, double x, double y);
  void OnButtonReleased(int button, double x, double y);

  void Reset();
  void UpdateCamera(glm::vec3 &eye, glm::vec3 &lookAt, glm::vec3 &up);
  void GetCameraVectors(glm::vec3 &eye,glm::vec3 &lookAt,glm::vec3 &up);

private:
  int screenWidth;
  int screenHeight;
  OpenGLManager *manager;
  OpenGLProgram *program;
  Square *square;
  CrossHairModel *crossHairModel;
  IObject *crossHair;
  IObject *crossHairLocal;
  SquareModel *model;
  Camera *camera;
  InputManager *inputManager;

  Television *television;
  CameraBasic *tvCamera;
  OpenGLProgram *tvProgram;

};

#endif
