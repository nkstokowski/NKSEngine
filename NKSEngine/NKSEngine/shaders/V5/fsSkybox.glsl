#version 430

in vec3 TexDir;
out vec4 fragColor;
uniform samplerCube myTexture;

void main()
{
	fragColor = texture(skybox, TexDir);
}