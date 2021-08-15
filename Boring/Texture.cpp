#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"

using namespace std;


Texture::Texture() {}
Texture::Texture(const char* path)
{
	int w;
	int h;
	int comp;
	unsigned char* image = stbi_load(path, &w, &h, &comp, STBI_rgb_alpha);

	if (image == nullptr)
		throw(std::string("Failed to load texture"));

	glGenTextures(1, &texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (comp == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	else if (comp == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image);

}


Texture::~Texture()
{
	glDeleteTextures(1, &texture_id);
}
