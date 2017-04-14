#version 430
out vec4 fragColor;

in float red;

layout(location=5) uniform float time;

void main()
{
	float green = (sin(time) + 1) / 2;
	fragColor = vec4(red, green, 0, 1);
}