#pragma once

#include "Lib.h"

#include <string>
#include <stdio.h>

namespace rendering
{

	//http://repository-of-projects.googlecode.com/svn/trunk/OpenGLES/11ES2SimpleTexture2D/main.cpp
	using namespace std;

	class CTextureWrapper
	{
	private:
		const string mName;
		GLuint mTextureId;
		unsigned int mWidth, mHeight;
		unsigned char* mDataBuf;

	public:
		CTextureWrapper(const string& name);
		~CTextureWrapper(void);

		void bind();
	};

}
