#pragma once

#include <assert.h>
#include <string.h>
#include "stb_image.h"

#ifndef TEXTURE
#define TEXTURE

typedef struct Texture {
	unsigned int width;
	unsigned int height;
	unsigned int texture;
} Texture;

static Texture Texture_Init(const char* fileName) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);

	if (data == NULL) {
		assert("TEXTURE WITH PATH " && fileName && " NOT FOUND!");
		return Texture_Init("IMG_7749.jpg");
	}

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	char* delim = strchr(fileName, '.');
	char* type = NULL;
	if (delim != NULL) {
		type = delim + 1;
	}

	unsigned int format = GL_RGB;

	switch (type[0])
	{
		case 'j': format = GL_RGB; break;
		case 'p': format = GL_RGBA; break;
		case 'g': format = GL_RGBA; break;
		default: assert("UNSUPPORTED TEXTURE FILE TYPE!"); break;
	}

	// texture target specifier for texture object, mipmap level, format, sizing, data types, and then image data
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	Texture tex = { width,height,texture };

	return tex;
}

static inline void Texture_Bind(const Texture* texture) {
	glBindTexture(GL_TEXTURE_2D, texture->texture);
}

#endif // !TEXTURE
