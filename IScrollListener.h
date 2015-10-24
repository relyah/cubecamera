#ifndef _ISCROLLLISTENER_H_
#define _ISCROLLLISTENER_H_

#include <gtk/gtk.h>

class IScrollListener {

public:
  virtual void OnScroll(GdkScrollDirection dir) = 0;

};

#endif
