/*
 * Common.h
 *
 *  Created on: 09 Feb 2014
 *      Author: bert
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/vector_angle.hpp>

#define EPSILON  0.000001f

void DebugPrint(const char* name, const glm::vec4& v);
void DebugPrint(const char* name, const glm::vec3& v);

#endif /* COMMON_H_ */
