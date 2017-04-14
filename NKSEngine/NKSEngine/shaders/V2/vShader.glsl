#version 430

layout(location=0) in vec3 modelloc;

out float red;

layout(location=3) uniform float scale;

void main()
{
	gl_Position = vec4(modelloc * scale, 1);
	red = (modelloc.x + 1)/2;
}