#include "AbstractCamera.h"

AbstractCamera::AbstractCamera() {
  model = glm::mat4(1.0f);
  view = glm::mat4(1.0f);
  projection = glm::mat4(1.0f);
  isChanged = false;
}

AbstractCamera::~AbstractCamera() {

}

bool AbstractCamera::IsChanged() {
  return isChanged;
}

glm::mat4 AbstractCamera::GetModel() {
  return model;
}

glm::mat4 AbstractCamera::GetView() {
  return view;
}

glm::mat4 AbstractCamera::GetProjection() {
  return projection;
}

