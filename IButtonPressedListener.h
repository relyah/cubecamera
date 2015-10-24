#ifndef _IBUTTONPRESSEDLISTENER_H_
#define _IBUTTONPRESSEDLISTENER_H_

class IButtonPressedListener {

public:
  virtual void OnButtonPressed(int button, double x, double y) = 0;
};

#endif
