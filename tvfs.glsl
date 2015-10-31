#version 130 

in vec2 out_texcoord;

uniform sampler2D texture;

out vec4 fragment_colour; // final colour of surface

void main () {	
	fragment_colour = texture2D(texture,out_texcoord); // vec4(1.0,1.0,0.0,1.0);//
}


