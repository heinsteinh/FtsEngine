#include "stdafx.h"
#include "Texture.h"


namespace rendering
{

	Texture::Texture()
	{ }

	GLuint Texture::getId()
	{
		return id;
	}

	int Texture::getWidth()
	{
		return width;
	}

	int Texture::getHeight()
	{
		return height;
	}
}