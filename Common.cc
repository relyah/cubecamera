#include "Common.h"
void DebugPrint(const char* name, const glm::vec4& v) {
	//std::cout << name << " x:" << v.x << " y:" << v.y << " z:" << v.z << std::endl;
  DebugPrint(name,glm::vec3(v));
}

void DebugPrint(const char* name, const glm::vec3& v) {
	std::cout << name << " x:" << v.x << " y:" << v.y << " z:" << v.z << std::endl;
}
