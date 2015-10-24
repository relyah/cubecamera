#ifndef _IHITABLE_H_
#define _IHITABLE_H_

#include "Ray.h"

class IHitable {

public:
  virtual ~IHitable() {};

  virtual void Intersect(Ray &ray) = 0;
};

#endif
