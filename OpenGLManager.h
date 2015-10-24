#ifndef OPENGLMANAGER_H_
#define OPENGLMANAGER_H_

#define GLFW_INCLUDE_GLCOREARB 1 // makes the header include the modern GL/glcorearb.h header (OpenGL/gl3.h on OS X) instead of the regular OpenGL header.

#include <epoxy/gl.h>

#include "AdminBase.h"

class OpenGLManager : public AdminBase {

public:
  OpenGLManager();
  virtual ~OpenGLManager();

  virtual void Init(OpenGLManager *manager);/* {

    OpenGLManager::manager = manager;

    glDebugMessageCallback(debug_callback, this);
    glDebugMessageCallbackARB(debug_callback, this);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // required ???

    //Controlling the volume of debug output.
    GLuint unusedIds = 0;
    //glDebugMessageControlARB(enum source, enum type, enum severity, sizei count, const uint* ids, boolean enabled).
    glDebugMessageControlARB(GL_DONT_CARE,
                             GL_DONT_CARE,
                             GL_DONT_CARE,
                             0,
                             &unusedIds,
                             true);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    }*/

  virtual void onDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar* message) const {
		fprintf(stderr, "MESSAGE: %s\n", (char *) message);
    }

protected:
  static OpenGLManager *manager;

  static void APIENTRY debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam) {
		reinterpret_cast<const OpenGLManager *>(userParam)->onDebugMessage(source, type, id, severity, length, message);
	}

};


#endif
