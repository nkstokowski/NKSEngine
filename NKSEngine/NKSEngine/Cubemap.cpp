#include "Cubemap.h"

bool Cubemap::load(vector<const GLchar*> faces)
{
	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	FIBITMAP* image;
	FIBITMAP* image32Bit;

	for (int i = 0; i < 6; i++) {
		image = FreeImage_Load(FreeImage_GetFileType(faces[i], 0), faces[i]);
		if (image == nullptr) {
			return false;
		}

		image32Bit = FreeImage_ConvertTo32Bits(image);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_SRGB_ALPHA,
			FreeImage_GetWidth(image32Bit),
			FreeImage_GetHeight(image32Bit),
			0,
			GL_BGRA,
			GL_UNSIGNED_BYTE,
			(void*)FreeImage_GetBits(image32Bit));

		FreeImage_Unload(image);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}

bool Cubemap::render()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, textID);
	return true;
}

Cubemap::Cubemap()
{
}


Cubemap::~Cubemap()
{
}
