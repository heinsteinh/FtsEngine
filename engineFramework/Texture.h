#pragma once

#include "Lib.h"

namespace rendering
{

	class Texture
	{
		friend class SpriteManager;

	private:
		Texture();
		GLuint id;
		int width, height;

	public:
		GLuint getId();
		int getWidth();
		int getHeight();
	};
}