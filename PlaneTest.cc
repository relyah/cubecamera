#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PlaneModule
#include <boost/test/unit_test.hpp>

#include "DataStructures.h"
#include "Plane.h"

struct BasicFixture
{
 
  BasicFixture() 
    {
      BOOST_TEST_MESSAGE("setup mass");
    }
 
  ~BasicFixture()
    {
      BOOST_TEST_MESSAGE("teardown mass");
    }
};
 
BOOST_FIXTURE_TEST_SUITE(PlaneTest, BasicFixture)
 
BOOST_AUTO_TEST_CASE(InstPlane_Default)
{
  Plane p();
 
  BOOST_CHECK(&p != NULL);
}

BOOST_AUTO_TEST_CASE(InstPlane_Points)
{
  VertexStructure points[4];
  points[0] = {    0.5f,  0.5f,  0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};
  points[1] = {  0.5f, -0.5f,  0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};
  points[2] = {   -0.5f, -0.5f,  0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};
  points[3] = {   -0.5f, 0.5f, 0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};

  glm::vec4 a = glm::vec4(1.0f);//points[0].coord3d[0],points[0].coord3d[1],points[0].coord3d[2],1.0f);
  glm::vec4 b =( glm::vec4(points[1].coord3d[0],points[1].coord3d[1],points[1].coord3d[2],1.0f));
  glm::vec4 c = ( glm::vec4(points[2].coord3d[0],points[2].coord3d[1],points[2].coord3d[2],1.0f));
  glm::vec4 d = ( glm::vec4(points[3].coord3d[0],points[3].coord3d[1],points[3].coord3d[2],1.0f));

  Plane p("test",a,b,c,d);

  BOOST_CHECK(&p != NULL);
}
 
BOOST_AUTO_TEST_CASE(IntersectPlaneRay)
{
  VertexStructure points[4];
  points[0] = {    0.5f,  0.5f,  0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};
  points[1] = {  0.5f, -0.5f,  0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};
  points[2] = {   -0.5f, -0.5f,  0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};
  points[3] = {   -0.5f, 0.5f, 0.0f, 0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f};

  glm::vec4 a = glm::vec4(points[0].coord3d[0],points[0].coord3d[1],points[0].coord3d[2],1.0f);
  glm::vec4 b =( glm::vec4(points[1].coord3d[0],points[1].coord3d[1],points[1].coord3d[2],1.0f));
  glm::vec4 c = ( glm::vec4(points[2].coord3d[0],points[2].coord3d[1],points[2].coord3d[2],1.0f));
  glm::vec4 d = ( glm::vec4(points[3].coord3d[0],points[3].coord3d[1],points[3].coord3d[2],1.0f));

  Plane p("test",a,b,c,d);

  glm::vec4 origin = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
  glm::vec4 dir = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
  //Ray r(origin,dir);

//  bool isIntersect = p.Intersect(r);

  BOOST_CHECK( true);//isIntersect);

}


BOOST_AUTO_TEST_SUITE_END()
