/*
 * Plane.h
 *
 *  Created on: 08 Feb 2014
 *      Author: bert
 */

#ifndef PLANE_H_
#define PLANE_H_

#include <iostream>
#include <string>

#define GLM_MESSAGES
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Ray.h"

class Plane {
public:
	Plane();
	Plane(const char* name, glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d);
	virtual ~Plane();


	bool Intersect(Ray& ray, glm::vec4 *&pt_out);
	bool Intersect(Plane& other, Ray*& ray);

	void FindIntersection(Ray& ray, glm::vec4 *&p1, glm::vec4 *& p2);
	bool Contains(glm::vec4& p);
	bool Contains(glm::vec4& p1, glm::vec4& p2);

	std::string GetName() {
		return name;
	}

private:
	bool IsParallel(Plane& other);
	bool IsOverlap(Plane& other);
	Ray MakeRay(glm::vec4& p1, glm::vec4& p2);

	bool IsEqual(float x, float y) {
		return fabs(fabs(x) - fabs(y)) <= EPSILON;
	}

	friend std::ostream& operator<<(std::ostream& ostream, const Plane& p) {
			return ostream << p.name << " n.x:" << p.normal.x << " n.y:" << p.normal.y << " n.z:" << p.normal.z << " d:" << p.depth << std::endl;
		}

	std::string name;
	glm::vec4 a;
	glm::vec4 b;
	glm::vec4 c;
	glm::vec4 d;

	Ray ab;
	Ray bc;
	Ray cd;
	Ray ad;

	float lenab;
	float lenbc;

	glm::vec3 normal;
	float depth;
};

#endif /* PLANE_H_ */
