#include "OpenGLApplication.h"

OpenGLApplication::OpenGLApplication(int screenWidth, int screenHeight)
  :screenWidth(screenWidth), screenHeight(screenHeight){
  logger->info("Starting OpenGLApplication...");

  manager = new OpenGLManager();
  program = new OpenGLProgram(string("cube.vs.glsl"),string("cube.fs.glsl"));
  tvProgram = new OpenGLProgram(string("tvvs.glsl"),string("tvfs.glsl"));
  inputManager = new InputManager();

  camera = new Camera(program, screenWidth, screenHeight);
  tvCamera = new CameraBasic(screenWidth, screenHeight);
  model = new SquareModel(camera,screenWidth, screenHeight);
  square = new Square(program, model, false);
  television = new Television(tvProgram,tvCamera,square);
  crossHairModel = new CrossHairModel();
  crossHair = new CrossHair(program,crossHairModel);
  crossHairLocal = new CrossHair(program,model);

  tvProgram->SetIsClear(false);
  tvProgram->SetCamera(tvCamera);
  tvProgram->AddObject(television);

  program->SetIsClear(true);
  program->SetCamera(camera);
  program->AddObject(square);
  program->AddObject(crossHair);
  program->AddObject(crossHairLocal);
  program->AddObject(tvProgram);

  inputManager->RegisterListener((IKeyReleasedListener*)model);
  inputManager->RegisterListener((IKeyReleasedListener*)camera);
  inputManager->RegisterListener((IScrollListener*)camera);
  inputManager->RegisterListener((IDragListener*)camera);
  inputManager->RegisterListener((IButtonPressedListener*)camera);
  inputManager->RegisterListener((IButtonReleasedListener*)camera);
}

OpenGLApplication::~OpenGLApplication() {
  delete square;
  delete crossHair;
  delete crossHairLocal;
  delete crossHairModel;
  delete model;
  delete camera;
  delete program;
  delete manager;
  delete inputManager;
  delete television;
  delete tvProgram;
  delete tvCamera;
  logger->info("Stopped OpenGLApplication.");
  logger = 0;
}

void OpenGLApplication::Init() {
  logger->info("Init OpenGLApplication...");

  manager->Init(manager);
  program->Init();
}

void OpenGLApplication::Reset() {
  model->Reset();
  camera->Reset();
}

void OpenGLApplication::Render() {
  //logger->info("Render OpenGLApplication...");

  program->Render();
}

void OpenGLApplication::Shutdown() {
  logger->info("Shutdown OpenGLApplication...");
}

void OpenGLApplication::UpdateCamera(glm::vec3 &eye, glm::vec3 &lookAt, glm::vec3 &up) {
  camera->Update(eye,lookAt,up);
}

void OpenGLApplication::GetCameraVectors(glm::vec3 &eye,glm::vec3 &lookAt,glm::vec3 &up) {

  glm::vec3 cEye = camera->GetEye();
  glm::vec3 cLookAt = camera->GetLookAt();
  glm::vec3 cUp = camera->GetUp();

  eye.x = cEye.x;
  eye.y = cEye.y;
  eye.z = cEye.z;

  lookAt.x = cLookAt.x;
  lookAt.y = cLookAt.y;
  lookAt.z = cLookAt.z;

  up.x = cUp.x;
  up.y = cUp.y;
  up.z = cUp.z;
}

void OpenGLApplication::OnKeyReleased(int key) {
  inputManager->OnKeyReleased(key);
}

void OpenGLApplication::OnScroll(GdkScrollDirection dir) {
  inputManager->OnScroll(dir);
}

void OpenGLApplication::OnDrag(double x, double y) {
  inputManager->OnDrag(x,y);
}

void OpenGLApplication::OnButtonPressed(int button, double x, double y) {
  inputManager->OnButtonPressed(button,x,y);
}

void OpenGLApplication::OnButtonReleased(int button, double x, double y) {
  inputManager->OnButtonReleased(button,x,y);
}
