#ifndef _INTERSECTOR_H_
#define _INTERSECTOR_H_

#include <vector>

#include "AdminBase.h"
#include "ICamera.h"
#include "IDragListener.h"
#include "IButtonPressedListener.h"
#include "IButtonReleasedListener.h"
#include "IHitable.h"

typedef std::vector<IHitable*> THitList;

class Intersector : AdminBase, public IButtonPressedListener, public IButtonReleasedListener, public IDragListener {

public:
  Intersector(ICamera *camera);
  virtual ~Intersector();

  virtual void OnDrag(double x, double y);
  virtual void OnButtonPressed(int button, double x, double y);
  virtual void OnButtonReleased(int button, double x, double y);

  void Add(IHitable *hitObject);

private:
  ICamera *camera;

  bool isPressed;
  double x;
  double y;

  THitList hitList;

  glm::vec4 CalcDir();
};

#endif
