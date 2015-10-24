#include "InputManager.h"

InputManager::InputManager() {
  keyReleasedListeners = TKeyReleasedListeners();
  scrollListeners = TScrollListeners();
  dragListeners = TDragListeners();
  buttonPressedListeners = TButtonPressedListeners();
  buttonReleasedListeners = TButtonReleasedListeners();
}

InputManager::~InputManager() {
  keyReleasedListeners.clear();
  scrollListeners.clear();
  dragListeners.clear();
  buttonPressedListeners.clear();
  buttonReleasedListeners.clear();
}

void InputManager::RegisterListener(IKeyReleasedListener *l) {
  keyReleasedListeners.push_back(l);
}

void InputManager::RegisterListener(IScrollListener *l) {
  scrollListeners.push_back(l);
}

void InputManager::RegisterListener(IDragListener *l) {
  dragListeners.push_back(l);
}

void InputManager::RegisterListener(IButtonPressedListener *l) {
  buttonPressedListeners.push_back(l);
}

void InputManager::RegisterListener(IButtonReleasedListener *l) {
  buttonReleasedListeners.push_back(l);
}

void InputManager::OnKeyReleased(int key) {
  if (keyReleasedListeners.size()==0) {return;}

  for (TKeyReleasedListeners::iterator it = keyReleasedListeners.begin() ; it != keyReleasedListeners.end(); ++it) {
    (*it)->OnKeyReleased(key);
  }
}

void InputManager::OnScroll(GdkScrollDirection dir) {
  if (scrollListeners.size()==0) {return;}

  for (TScrollListeners::iterator it = scrollListeners.begin() ; it != scrollListeners.end(); ++it) {
    (*it)->OnScroll(dir);
  }
}

void InputManager::OnDrag(double x, double y) {
  if (dragListeners.size()==0) {return;}

  for (TDragListeners::iterator it = dragListeners.begin() ; it != dragListeners.end(); ++it) {
    (*it)->OnDrag(x,y);
  }
}

void InputManager::OnButtonPressed(int button, double x, double y) {
  if (buttonPressedListeners.size()==0) {return;}

  for (TButtonPressedListeners::iterator it = buttonPressedListeners.begin() ; it != buttonPressedListeners.end(); ++it) {
    (*it)->OnButtonPressed(button, x,y);
  }
}

void InputManager::OnButtonReleased(int button, double x, double y) {
  if (buttonReleasedListeners.size()==0) {return;}

  for (TButtonReleasedListeners::iterator it = buttonReleasedListeners.begin() ; it != buttonReleasedListeners.end(); ++it) {
    (*it)->OnButtonReleased(button, x,y);
  }
}

