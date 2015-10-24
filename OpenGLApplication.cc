#include "OpenGLApplication.h"

#include "Ray.h"

OpenGLApplication::OpenGLApplication(int screenWidth, int screenHeight)
  :screenWidth(screenWidth), screenHeight(screenHeight){
  logger->info("Starting OpenGLApplication...");

  manager = new OpenGLManager();
  program = new OpenGLProgram();
  inputManager = new InputManager();

  camera = new Camera(program, screenWidth, screenHeight);
  model = new SquareModel(camera,screenWidth, screenHeight);
  square = new Square(program, model);
  glm::vec4 v1 = glm::vec4(1.0f);
  glm::vec4 v2 = glm::vec4(1.0f);
  Ray r(v1,v2);
  (square)->Intersect(r);
  crossHairModel = new CrossHairModel();
  crossHair = new CrossHair(program,crossHairModel);
  crossHairLocal = new CrossHair(program,model);

  program->SetCamera(camera);

  program->AddObject(square);
  program->AddObject(crossHair);
  program->AddObject(crossHairLocal);

  intersector = new Intersector(camera);
  intersector->Add(dynamic_cast<IHitable*>(square));

  inputManager->RegisterListener((IKeyReleasedListener*)model);
  inputManager->RegisterListener((IKeyReleasedListener*)camera);
  inputManager->RegisterListener((IScrollListener*)camera);
  inputManager->RegisterListener((IDragListener*)camera);
  inputManager->RegisterListener((IButtonPressedListener*)camera);
  inputManager->RegisterListener((IButtonReleasedListener*)camera);
  inputManager->RegisterListener((IDragListener*)intersector);
  inputManager->RegisterListener((IButtonPressedListener*)intersector);
  inputManager->RegisterListener((IButtonReleasedListener*)intersector);
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
  delete intersector;
  logger->info("Stopped OpenGLApplication.");
  logger = 0;
}

void OpenGLApplication::Init() {
  logger->info("Init OpenGLApplication...");

  manager->Init(manager);
  program->Init();
}

void OpenGLApplication::Render() {
  //logger->info("Render OpenGLApplication...");

  program->Render();
}

void OpenGLApplication::Shutdown() {
  logger->info("Shutdown OpenGLApplication...");
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
