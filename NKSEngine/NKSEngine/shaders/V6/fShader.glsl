#version 430

out vec4 fragColor;
in float red;
in vec3 fragnormal;
in vec3 fragloc;
in vec2 fragUV;
uniform sampler2D myTexture;

// Material Data
// x = ambient component
// y = diffuse component
// z = specular component
// w = specular alpha
layout(location=6) uniform vec4 materialData;

layout(location=7) uniform vec3 cameraloc;
layout(location=8) uniform vec3 lightloc;
layout(location=5) uniform float time;

void main()
{
	vec3 L = normalize(lightloc - fragloc);
	vec3 V = normalize(cameraloc - fragloc);
	vec3 H = normalize(L + V);
	
	vec3 N = normalize(fragnormal);
	
	float diffuse = materialData.y * max( 0, dot(L, N));
	float specular = materialData.z * pow( max( dot(H, N), 0), materialData.w);
	
	float bright = materialData.x + diffuse + specular;
	//fragColor = texture(myTexture, fragUV);
	vec4 tex = texture(myTexture, fragUV);
	
	fragColor = tex * bright;
	fragColor.w = tex.w;
	
	//fragColor = vec4(cameraloc, 1);
	//fragColor = vec4(fragloc, 1);
}