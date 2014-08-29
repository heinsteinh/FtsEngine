#ifndef IPHONE_GRAPHICS_H
#define IPHONE_GRAPHICS_H

#define IP_SAFE_RELEASE(x) if ( x ) { x->release(); x = 0; }

#include "Engine.h"

enum IphoneVertexFormat
{
	IVF_POSITION	= (1 << 0),
	IVF_NORMAL		= (1 << 1),
	IVF_TEXCOORD0	= (1 << 2),
	IVF_TEXCOORD1	= (1 << 3),
	IVF_COLOR		= (1 << 4)
};

class IphoneTexture
{
public:
	virtual void release(void) = 0;
};

class IphoneVertexBuffer
{
public:
	virtual void release(void) = 0;
	virtual void * lock(void) = 0;
	virtual void   unlock(unsigned int  vcount) = 0;
};

class IphoneIndexBuffer
{
public:
	virtual void release(void) = 0;
	virtual void * lock(void) = 0;
	virtual void   unlock(void) = 0;
};

class IphoneGraphics
{
public:

	virtual void initExtensions() = 0;
	
	virtual IphoneTexture*      createIphoneTexture(const unsigned char *data, unsigned int width, unsigned int height) = 0;
	virtual IphoneVertexBuffer* createIphoneVertexBuffer(unsigned int fvf, const void *vbuffer, unsigned int vcount, bool dynamic) = 0;
	virtual IphoneIndexBuffer*  createIphoneIndexBuffer(const unsigned short *indices, unsigned int icount, bool dynamic) = 0;


	virtual void                setActiveTexture(IphoneTexture *texture) = 0;
	virtual IphoneTexture*		getActiveTexture(void) = 0;

	virtual void                renderTriangleList(const glm::mat4 &transform,IphoneVertexBuffer *vb,IphoneIndexBuffer *ib) = 0;
	virtual void                renderTriangleList(const glm::mat4 &transform,	IphoneVertexBuffer *vb,	IphoneIndexBuffer *ib,unsigned int vcount, unsigned int tcount) = 0;

	virtual void                setViewMatrix(const glm::mat4 &view) = 0;
	virtual void                setProjectionMatrix(const glm::mat4 &projection) = 0;
	virtual void                setAlphaTest(bool state, float value) = 0;
	virtual void                setZenable(bool state) = 0;
	
};


IphoneGraphics * createIphoneGraphics(void);
void             releaseIphoneGraphics(IphoneGraphics *ig);

extern IphoneGraphics *gIphoneGraphics;

#endif
