#include "AdminBase.h"

AdminBase::AdminBase() {
  logger = Logger::GetLogger();
}

AdminBase::~AdminBase() {
  logger = 0;
}
