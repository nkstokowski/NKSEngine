#version 430

layout(location=0) in vec3 modelloc;
layout(location=1) in vec3 modelnorm;

out vec3 fragnormal;
out vec3 fragloc;
out float red;
out vec2 fragUV;
in vec2 modelUV;

layout(location=3) uniform float scale;
layout(location=9) uniform mat4 modelWorld;
layout(location=4) uniform mat4 worldView;

void main()
{
	fragloc = modelloc;
	fragnormal = modelnorm;
	
	fragUV = modelUV;
	
	gl_Position = worldView * modelWorld * vec4(modelloc, 1);
	//gl_Position = worldView * vec4(modelloc, 1);
	red = (modelloc.x + 1)/2;
}