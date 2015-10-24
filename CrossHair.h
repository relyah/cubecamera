#ifndef _CROSSHAIR_H_
#define _CROSSHAIR_H_

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DataStructures.h"
#include "AbstractObject.h"

class CrossHair : public AbstractObject {

public:

  CrossHair(IOpenGLProgram *program, IModel *model);
  virtual ~CrossHair();

  virtual void Init();
  virtual void Render();
  virtual void Shutdown();

private:
  GLuint vboPoints;
  GLuint attribute_vp, attribute_vn, attribute_vc;
  GLint uniform_p, uniform_v, uniform_m;
};

#endif
