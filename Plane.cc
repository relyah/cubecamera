/*
 * Plane.cpp
 *
 *  Created on: 08 Feb 2014
 *      Author: bert
 */

#include "Plane.h"

Plane::Plane() :
  name("Plane"), a(0), b(0), c(0), d(0), lenab(0), lenbc(0), depth(0) {

}
Plane::Plane(const char* name, glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d) : name(name), a(a), b(b), c(c), d(d)
{
  /*this->a = glm::vec4(_a);
    this->b =b;
    this->c =c;
    this->d=d;*/
  

  //std::cout << "hello " << a.x << std::endl;

  std::cout << "start plane " << std::endl;

  DebugPrint("a",this->a);
  DebugPrint("b",this->b);
  DebugPrint("c",this->c);
  DebugPrint("d",this->d);

	glm::vec3 v1 = glm::vec3(this->b-this->a);//b.x - a.x, b.y - a.y, b.z - a.z);
	glm::vec3 v2 = glm::vec3(this->c-this->a);//c.x - a.x, c.y - a.y, c.z - a.z);
  DebugPrint("v1",v1);
  DebugPrint("v2",v2);

	normal = glm::normalize(glm::cross(v1, v2));
  DebugPrint("n",normal);

	glm::vec3 p = glm::vec3(this->a);//a.x, a.y, a.z);
	depth = 1.0f * glm::dot(-normal, p);

	ab = MakeRay(this->a, this->b);
	bc = MakeRay(this->b, this->c);
	cd = MakeRay(this->c, this->d);
	ad = MakeRay(this->a, this->d);

	lenab = glm::length(glm::vec3(this->b-this->a));//b.x - a.x, b.y - a.y, b.z - a.z));
	lenbc = glm::length(glm::vec3(this->c-this->b));//c.x - b.x, c.y - b.y, c.z - b.z));
}

Plane::~Plane() {
}

bool Plane::Intersect(Ray& ray, glm::vec4*& pt_out) {

	//std::cout << name << std::endl;

  pt_out =NULL;

	std::cout << "Normal x:" << normal.x << " y:" << normal.y << " z:" << normal.z << " depth:" << depth << std::endl;

	glm::vec4 L = glm::vec4(normal.x, normal.y, normal.z, depth);
	glm::vec4 origin = ray.GetOrigin();
	glm::vec4 S = glm::vec4(origin.x, origin.y, origin.z, 1.0f);
	glm::vec4 dir = ray.GetDir();
	glm::vec4 V = glm::vec4(dir.x, dir.y, dir.z, 0.0f);

	//std::cout << "S x:" << S.x << " y:" << S.y << " z:" << S.z << std::endl;
	//std::cout << "V x:" << V.x << " y:" << V.y << " z:" << V.z << std::endl;

	float denum = glm::dot(L, V);
	float num = glm::dot(L, S);

	//std::cout << "num: " << num << " denum:" << denum << std::endl;

	//is the line parallel to the plane ?
	if (fabs(denum) < EPSILON) {
		//is the line inside the plane ?
		if (fabs(num) < EPSILON) {
			std::cout << "Inside plane" << std::endl;

			return true;
		}
		return false; //line is parallel to the plane but outside (above or below)
	}

	float t = -num / denum;

	glm::vec4 pt = ray.GetPoint(t);
  pt_out = new glm::vec4(pt);
	std::cout << "Intersection Pt x:" << pt.x << " y:" << pt.y << " z:" << pt.z << std::endl;

	float dad = ad.GetDistanceToPoint(pt);
	float dbc = bc.GetDistanceToPoint(pt);
	float dab = ab.GetDistanceToPoint(pt);
	float dcd = cd.GetDistanceToPoint(pt);

  std::cout << "dad: " << dad << ", dbc: " << dbc << ", dab: " << dab << ", dcd: " << dcd << std::endl;

	bool intersect = dad <= lenab && dbc <= lenab && dab <= lenbc && dcd <= lenbc;

	return intersect;

}

bool Plane::Intersect(Plane& plane, Ray*& ray) {

	std::cout << "Testing this->Plane: " << this->name << " other->Plane: " << plane.name << std::endl;

	bool isParallel = IsParallel(plane);
	bool isOverlap = IsOverlap(plane);

	std::cout << "IsParallel:" << isParallel << " IsOverlap:" << isOverlap << std::endl;

	if (isParallel) {
		ray = NULL;
		return isOverlap;
	}

	glm::vec3 N1 = glm::vec3(this->normal.x, this->normal.y, this->normal.z);
	std::cout << "N1 x:" << N1.x << " y:" << N1.y << " z:" << N1.z << std::endl;
	glm::vec3 N2 = glm::vec3(plane.normal.x, plane.normal.y, plane.normal.z);
	std::cout << "N2 x:" << N2.x << " y:" << N2.y << " z:" << N2.z << std::endl;
	glm::vec3 V = glm::normalize(glm::cross(N1, N2));
	std::cout << "V x:" << V.x << " y:" << V.y << " z:" << V.z << std::endl;

	glm::mat3 M = glm::transpose(glm::mat3(N1, N2, V));

	glm::mat3 invM = glm::inverse(M);

	std::cout << "this->depth: " << this->depth << " plane.depth: " << plane.depth << std::endl;
	glm::vec3 D = glm::vec3(-this->depth, -plane.depth, 0.0f);

	glm::vec3 Q = invM * D;

	std::cout << "Q x:" << Q.x << " y:" << Q.y << " z:" << Q.z << std::endl;

	glm::vec4 Q4 = glm::vec4(Q.x, Q.y, Q.z, 1.0f);
	glm::vec4 V4 = glm::vec4(V.x, V.y, V.z, 0.0f);
	ray = new Ray(Q4, V4);

	return true;
}

void Plane::FindIntersection(Ray& ray, glm::vec4 *&p1, glm::vec4 *& p2) {
	Ray rays[4];
	rays[0] = ab;
	rays[1] = bc;
	rays[2] = cd;
	rays[3] = ad;

//	p1 = new glm::vec4;
//	p2 = new glm::vec4;

//	glm::vec4* ps[2];
//	ps[0] = p1;
//	ps[1] = p2;
	unsigned int index = 0;
	for (int i = 0; i < 4; i++) {
		glm::vec4* temp = NULL;
		if (rays[i].Intersect(ray, temp)) {
			//ps[index] = temp;
			if (index == 0)
				p1 = temp;
			else if (index == 1)
				p2 = temp;
			std::cout << "Intersect ps" << index << " x:" << temp->x << " y:" << temp->y << " z:" << temp->z << std::endl;
			index++;
			if (index >= 2) {
				return;
			}
		}
	}

}

bool Plane::Contains(glm::vec4& pt) {
	std::cout << "Testing contains pt x:" << pt.x << " y:" << pt.y << " z:" << pt.z << std::endl;

	//Model::DebugPrint("A->", a);
	//Model::DebugPrint("<-D", d);
	float dad = ad.GetDistanceToPoint(pt);
	std::cout << "dad:" << dad << std::endl;

	//Model::DebugPrint("B->", b);
	//Model::DebugPrint("<-C", c);
	float dbc = bc.GetDistanceToPoint(pt);
	std::cout << "dbc:" << dbc << std::endl;

	//Model::DebugPrint("A->", a);
	//Model::DebugPrint("<-b", b);
	float dab = ab.GetDistanceToPoint(pt);
	std::cout << "dab:" << dab << std::endl;

	//Model::DebugPrint("C->", c);
	//Model::DebugPrint("<-D", d);
	float dcd = cd.GetDistanceToPoint(pt);
	std::cout << "dcd:" << dcd << std::endl;

	std::cout << "lenab: " << lenab << " lenbc: " << lenbc << std::endl;

	return dad <= lenab && dbc <= lenab && dab <= lenbc && dcd <= lenbc;
}

bool Plane::Contains(glm::vec4& p1, glm::vec4& p2) {
	std::cout << "Testing contains p1 x:" << p1.x << " y:" << p1.y << " z:" << p1.z << std::endl;
	std::cout << "Testing contains p2 x:" << p2.x << " y:" << p2.y << " z:" << p2.z << std::endl;
	bool isContainsP1 = Contains(p1);
	bool isContainsP2 = Contains(p2);
	std::cout << "isContainsP1:" << isContainsP1 << " isContainsP2:" << isContainsP2 << std::endl;
	return isContainsP1 && isContainsP2;
}

bool Plane::IsParallel(Plane& other) {
	std::cout << "this_normal x:" << this->normal.x << " y:" << this->normal.y << " z:" << this->normal.z << std::endl;
	std::cout << "other.normal x:" << other.normal.x << " y:" << other.normal.y << " z:" << other.normal.z << std::endl;
	return IsEqual(this->normal.x, other.normal.x) && IsEqual(this->normal.y, other.normal.y)
    && IsEqual(this->normal.z, other.normal.z);
}
bool Plane::IsOverlap(Plane& other) {
//assumes planes are parallel
	std::cout << "this->depth:" << this->depth << " other.depth:" << other.depth << std::endl;
	return IsEqual(this->depth, other.depth);
}

Ray Plane::MakeRay(glm::vec4& p1, glm::vec4& p2) {
	return Ray::MakeRay(p1, p2);
}
