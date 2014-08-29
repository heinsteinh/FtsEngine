#pragma once

#include "Engine.h"

#include <string>
#include <stdio.h>
using namespace std;

class CTexture
{
private:
	const string mName;
	GLuint mTextureId;
	unsigned int mWidth, mHeight;
	unsigned char* mDataBuf;

	int MinFilter;
	int MagFilter;
	float WrapTexture;

public:
	CTexture(const string& name);
	~CTexture(void);

	void bind();
	GLuint getTextureId() { return mTextureId; };
	void Set(int id = 0);

	inline void SetFilter(int min, int mag){
		MinFilter = min;
		MagFilter = mag;
	}
};
