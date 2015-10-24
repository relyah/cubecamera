#version 130
in vec3 vp; //points   layout (location = 0)
in  vec3 vn; //normal   layout (location = 1)
in  vec3 vc; //colour   layout (location = 2)

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 position_eye;
out vec3 normal_eye;
out vec3 colour;

void main () {
  gl_PointSize = 20.0f;

  position_eye = vec3(view * model * vec4(vp, 1.0f));
  normal_eye = vec3(view * model * vec4(vn, 1.0));


 gl_Position = projection * vec4 (position_eye,1.0f); //vp.x,vp.y,vp.z, 1.0); //

// gl_Position = vec4 (vp.x,vp.y,vp.z, 1.0);

  colour =vc;

}
