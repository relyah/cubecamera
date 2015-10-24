#include "OpenGLManager.h"

OpenGLManager *OpenGLManager::manager = 0;

OpenGLManager::OpenGLManager() {
  logger->info("Starting OpenGLManager...");
}

OpenGLManager::~OpenGLManager() {
	logger->info("Stopped OpenGLManager.");
}

void OpenGLManager::Init(OpenGLManager *manager) {

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

  // *** POINT SIZE ***
  //glEnable(GL_PROGRAM_POINT_SIZE); //use gl_PointSize in shader
  glDisable(GL_PROGRAM_POINT_SIZE);glPointSize(40.0f); //use glPointSize from the code 

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

/*void OpenGLManager::Init() {
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
