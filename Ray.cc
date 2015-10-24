/*
 * Ray.cpp
 *
 *  Created on: 08 Feb 2014
 *      Author: bert
 */

#include "Ray.h"

Ray::Ray() :
		origin(0), dir(0) {

}

Ray::Ray(glm::vec4& origin, glm::vec4& dir) :
		origin(origin) {
	this->dir = glm::normalize(dir);
}

Ray::~Ray() {
}

bool Ray::Intersect(Ray& other, glm::vec4 *& pt) {
	//source: http://mathforum.org/library/drmath/view/62814.html
	glm::vec3 D1 = glm::vec3(this->dir.x, this->dir.y, this->dir.z);
	glm::vec3 D2 = glm::vec3(other.dir.x, other.dir.y, other.dir.z);

	glm::vec4 O4 = other.origin - this->origin;
	glm::vec3 O = glm::vec3(O4.x, O4.y, O4.z);

	glm::vec3 left = glm::cross(D1, D2);
	glm::vec3 right = glm::cross(O, D2);

	glm::vec3 nleft = glm::normalize(left);
	glm::vec3 nright = glm::normalize(right);

	bool isParallel = IsAbsEqual(nleft.x, nright.x) && IsAbsEqual(nleft.y, nright.y) && IsAbsEqual(nleft.z, nright.z);
	bool isIntersect = false;
	if (isParallel) {
		float magleft = glm::length(left);
		if (IsZero(magleft)) {
			std::cout << "???Rays do not intersect.???" << std::endl;
			isIntersect = false;
		} else {
			isIntersect = true;
			float magright = glm::length(right);
			float a = magright / magleft;

			bool isOppDir = IsNegEqual(nleft.x, nright.x) && IsNegEqual(nleft.y, nright.y) && IsNegEqual(nleft.z, nright.z);
			if (isOppDir) {
				std::cout << "Flipping a." << std::endl;
				a *= -1.0f;
			}

			glm::vec4 p = this->GetPoint(a);

			pt =  new glm::vec4(p.x, p.y, p.z, p.w);

			std::cout << "a:" << a << " pt x:" << pt->x << " y:" << pt->y << " z:" << pt->z << std::endl;
		}

	} else {
		std::cout << "Rays do not intersect." << std::endl;
		isIntersect = false;
		pt = NULL;
	}

	return isIntersect;
}

float Ray::GetDistanceToPoint(glm::vec4 pt) {
	glm::vec3 pt3 = glm::vec3(pt.x, pt.y, pt.z);
	glm::vec3 origin3 = glm::vec3(origin.x, origin.y, origin.z);
	glm::vec3 dir3 = glm::vec3(dir.x, dir.y, dir.z);
	return glm::length(glm::cross(pt3 - origin3, dir3)) / glm::length(dir3);
}

Ray Ray::MakeRay(glm::vec4& p1, glm::vec4& p2) {
	glm::vec4 dir = p2 - p1;
	return Ray(p1, dir);
}
