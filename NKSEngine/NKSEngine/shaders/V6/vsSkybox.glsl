#version 430

layout(location=0) in vec3 modelloc;
layout(location=4) uniform mat4 worldView;
out vec3 TexDir;

void main()
{
	TexDir = modelloc;	
	gl_Position = worldView * vec4(modelloc, 1);
}