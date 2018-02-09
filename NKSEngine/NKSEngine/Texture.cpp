#include "Texture.h"
#include <iostream>

using namespace std;

bool Texture::render()
{
	glBindTexture(GL_TEXTURE_2D, textID);
	return true;
}

bool Texture::unload()
{
	glDeleteTextures(1, &textID);
	return true;
}

bool Texture::load(string textFile)
{

	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(textFile.c_str() , 0), textFile.c_str());
	if (image == nullptr) {
		printf("Texture Error: Texture file not found.");
		return false;
	}

	textfile = textFile;

	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);

	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_SRGB_ALPHA,
		FreeImage_GetWidth(image32Bit),
		FreeImage_GetHeight(image32Bit),
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32Bit));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	FreeImage_Unload(image32Bit);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

Texture::Texture()
{
}


Texture::~Texture()
{
}
