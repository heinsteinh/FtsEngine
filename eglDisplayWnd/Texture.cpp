#include "stdafx.h"
#include "Texture.h"

#include "TGA.h"
#include "Log.h"

CTexture::CTexture(const string& fileName) :mTextureId(-1), mName(fileName), mDataBuf(NULL)
{
	MinFilter = GL_NEAREST;
	MagFilter = GL_LINEAR;
	WrapTexture = GL_REPEAT;


	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	int imgWidth, imgHeight, imgBpp;
	char* fileToRead = (char*)fileName.c_str();

	mDataBuf = (unsigned char*)LoadTGA(fileToRead, &imgWidth, &imgHeight, &imgBpp);
	LOG_ERROR << "Texture %s loaded\nWidth: %d\nHeight: %d\nBpp: %d\n", fileName.c_str(), imgWidth, imgHeight, imgBpp;
	glTexImage2D(GL_TEXTURE_2D, 0, (imgBpp == 32) ? GL_RGBA : GL_RGB, imgWidth, imgHeight, 0, (imgBpp == 32) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, mDataBuf);

	mHeight = imgHeight;
	mWidth  = imgWidth;



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	// not using mipmap
	/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);*/
	
	// using mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] mDataBuf;

	GL_CHECK

}



CTexture::~CTexture(void)
{
	if (mDataBuf)
	{
		delete[] mDataBuf;
	}
	if (mTextureId>-1)
	{
		glDeleteTextures(1, &mTextureId);
		printf("delete texture %s success\n", mName.c_str());
	}
}


void CTexture::bind()
{
	glBindTexture(GL_TEXTURE_2D, mTextureId);
}



void CTexture::Set(int id)
{

	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, mTextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilter);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapTexture);
}