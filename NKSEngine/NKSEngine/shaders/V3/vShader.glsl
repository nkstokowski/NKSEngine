#version 430

layout(location=0) in vec3 modelloc;

out float red;

layout(location=3) uniform float scale;
layout(location=4) uniform mat4 worldView;

void main()
{
	gl_Position = worldView * vec4(modelloc, 1);
	red = (modelloc.x + 1)/2;
}