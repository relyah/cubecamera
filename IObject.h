#ifndef _IOBJECT_H_
#define _IOBJECT_H_

#include <epoxy/gl.h>

class IObject {
public:

  virtual ~IObject() {}

  virtual void Init() = 0;
  virtual void Render() = 0;
  virtual void Shutdown() = 0;

  virtual void Bind() = 0;
  virtual void Unbind() = 0;

  virtual GLuint GetColorTexture() = 0;

};

#endif
