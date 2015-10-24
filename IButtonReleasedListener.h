#ifndef _IBUTTONRELEASEDLISTENER_H_
#define _IBUTTONRELEASEDLISTENER_H_

class IButtonReleasedListener {

public:
  virtual void OnButtonReleased(int button, double x, double y) = 0;
};

#endif
