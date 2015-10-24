/*
 * Ray.h
 *
 *  Created on: 08 Feb 2014
 *      Author: bert
 */

#ifndef _RAY_H_
#define _RAY_H_

#include <iostream>

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Common.h"

class Ray {
public:
	Ray();
	Ray(glm::vec4& origin, glm::vec4& dir);
	virtual ~Ray();

	bool Intersect(Ray& other, glm::vec4 *& pt);

	glm::vec4 GetOrigin() {
		return origin;
	}
	glm::vec4 GetDir() {
		return dir;
	}

	glm::vec4 GetPoint(float t) {
		return origin + t * dir;
	}

	float GetDistanceToPoint(glm::vec4 pt);

	static Ray MakeRay(glm::vec4& p1, glm::vec4& p2);

private:
	bool IsAbsEqual(float x, float y) {
		return fabs(fabs(x) - fabs(y)) <= EPSILON;
	}
	bool IsNegEqual(float x, float y) {
		return fabs(x + y) <= EPSILON;
	}
	bool IsZero(float x) {
		return fabs(x) <= EPSILON;
	}

	glm::vec4 origin;
	glm::vec4 dir;

};

#endif /* RAY_H_ */
