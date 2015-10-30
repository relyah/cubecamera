 #version 130   

in vec3 vp;
in vec2 vt;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 out_texcoord;

void main () {  
	out_texcoord = vt;  
  gl_Position = projection * view * model * vec4(vp,1.0f);
}