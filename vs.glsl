#version 330
#extension GL_ARB_explicit_attrib_location: enable

layout(location = 0) in vec2 in_position;

void main()                           
{
gl_Position = vec4(in_position, 0.0, 1.0);
}


