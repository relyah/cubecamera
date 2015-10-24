#ifndef _ADMINBASE_H_
#define _ADMINBASE_H_

#include "Logger.h"

class AdminBase {

public:
  AdminBase();
  ~AdminBase();

protected:
  std::stringstream sstm;
  log4cpp::Category* logger;
};

#endif
