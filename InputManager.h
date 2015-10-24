#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <vector>

#include "IKeyReleasedListener.h"
#include "IScrollListener.h"
#include "IDragListener.h"
#include "IButtonPressedListener.h"
#include "IButtonReleasedListener.h"

typedef  std::vector<IKeyReleasedListener*> TKeyReleasedListeners;
typedef  std::vector<IScrollListener*> TScrollListeners;
typedef  std::vector<IDragListener*> TDragListeners;
typedef  std::vector<IButtonPressedListener*> TButtonPressedListeners;
typedef  std::vector<IButtonReleasedListener*> TButtonReleasedListeners;

class InputManager : public IKeyReleasedListener, public IScrollListener, public IDragListener, public IButtonPressedListener, public IButtonReleasedListener {

public:
  InputManager();
  virtual ~InputManager();

  virtual void OnKeyReleased(int key);
  virtual void OnScroll(GdkScrollDirection dir);
  virtual void OnDrag(double x, double y);
  virtual void OnButtonPressed(int button, double x, double y);
  virtual void OnButtonReleased(int button, double x, double y);

  void RegisterListener(IKeyReleasedListener *l);
  void RegisterListener(IScrollListener *l);
  void RegisterListener(IDragListener *l);
  void RegisterListener(IButtonPressedListener *l);
  void RegisterListener(IButtonReleasedListener *l);

private:
  TKeyReleasedListeners keyReleasedListeners;
  TScrollListeners scrollListeners;
  TDragListeners dragListeners;
  TButtonPressedListeners buttonPressedListeners;
  TButtonReleasedListeners buttonReleasedListeners;
};

#endif
