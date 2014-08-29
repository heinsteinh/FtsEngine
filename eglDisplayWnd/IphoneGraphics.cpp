#include "stdafx.h" 
#include "IphoneGraphics.h"


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h> // glMapBufferOES
#define glCheckFramebufferStatusEXT glCheckFramebufferStatus
#define glBindFramebufferEXT glBindFramebuffer
#define glCheckFramebufferStatusEXT glCheckFramebufferStatus
#define glFramebufferTexture2DEXT glFramebufferTexture2D
//#define glMapBuffer glMapBufferOES
//#define glUnmapBuffer glUnmapBufferOES
#define GL_DEPTH_COMPONENT24 GL_DEPTH_COMPONENT24_OES
#define GL_DEPTH_ATTACHMENT_EXT GL_DEPTH_ATTACHMENT
#define GL_FRAMEBUFFER_EXT GL_FRAMEBUFFER
#define GL_RENDERBUFFER_EXT GL_RENDERBUFFER
#define GL_WRITE_ONLY GL_WRITE_ONLY_OES
#define GL_COLOR_ATTACHMENT0_EXT GL_COLOR_ATTACHMENT0



// normal process
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

//declare here while define in CCEGLView.cpp
extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArrays;
extern PFNGLMAPBUFFEROESPROC glMapBuffer;
extern PFNGLUNMAPBUFFEROESPROC glUnmapBuffer;
extern PFNGLGETBUFFERPOINTERVOESPROC glGetBufferPointerv;



// <EGL/egl.h> exists since android 2.3
#include <EGL/egl.h>
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT = 0;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT = 0;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT = 0;


PFNGLMAPBUFFEROESPROC glMapBufferOESEXT = 0;
PFNGLUNMAPBUFFEROESPROC glUnmapBufferOESEXT = 0;




IphoneGraphics *gIphoneGraphics = 0;

#define USE_VBO_MAP 1

class MyIphoneTexture : public IphoneTexture
{
public:
	MyIphoneTexture(const unsigned char *data, unsigned int width, unsigned int height)
	{
		bool wrap = false;
		mTexture = 0;
		glGenTextures(1, &mTexture); // get a texture id.
		glBindTexture(GL_TEXTURE_2D, mTexture);

		// select modulate to mix texture with color for shading
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP_TO_EDGE);


		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	virtual void release(void)
	{
		if (mTexture != 0)
		{
			glDeleteTextures(1, &mTexture);
			mTexture = 0;
		}
	}

	//private:
	GLuint  mTexture;
};

unsigned int getFVFSize(unsigned int fvf)
{
	unsigned int ret = 0;
	if (fvf & IVF_POSITION)  ret += sizeof(float)* 3;
	if (fvf & IVF_NORMAL)	 ret += sizeof(float)* 3;
	if (fvf & IVF_TEXCOORD0) ret += sizeof(float)* 2;
	if (fvf & IVF_TEXCOORD1) ret += sizeof(float)* 2;
	if (fvf & IVF_COLOR)	 ret += sizeof(unsigned int);
	return ret;
}

class MyIphoneVertexBuffer : public IphoneVertexBuffer
{
public:


	MyIphoneVertexBuffer(unsigned int fvf, const void *_vbuffer, unsigned int vcount, bool dynamic)
	{

		mLocked = false;
		mStride = getFVFSize(fvf);
		mVertexCount = vcount;
		mVertexBuffer = 0;
		glGenBuffers(1, &mVertexBuffer);
		if (mVertexBuffer)
		{
			const void *vbuffer = _vbuffer;
			if (vbuffer == 0)
			{
				vbuffer = malloc(vcount*mStride);
			}

			glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, mStride*vcount, vbuffer, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			if (_vbuffer == 0)
			{
				free((void *)vbuffer);
			}
		}
#if USE_VDO_MAP
#else
		if (dynamic && mVertexBuffer)
		{
			mBackingStore = malloc(vcount*mStride);
		}
		else
		{
			mBackingStore = 0;
		}
#endif
	}

	~MyIphoneVertexBuffer(void)
	{
		release();
	}

	virtual void release(void)
	{
		if (mVertexBuffer)
		{
			glDeleteBuffers(1, &mVertexBuffer);
			mVertexBuffer = 0;
		}
#if USE_VDO_MAP
#else
		if (mBackingStore)
		{
			free(mBackingStore);
			mBackingStore = 0;
		}
#endif
	}

	virtual void * lock(void)
	{
		void *ret = 0;
		assert(mLocked == false);
		if (mVertexBuffer && mLocked == false)
		{
#if USE_VDO_MAP
			glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
#ifdef __APPLE__
			ret = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
#else
			ret = glMapBufferARB(GL_ARRAY_BUFFER, GL_WRITE_ONLY_ARB);
#endif
			glBindBuffer(GL_ARRAY_BUFFER, 0);
#else
			ret = mBackingStore;
#endif
			mLocked = true;
		}
		return ret;
	}

	virtual void   unlock(unsigned int vcount)
	{
		assert(mLocked == true);
		if (mLocked)
		{
#if USE_VDO_MAP
			glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

#ifdef __APPLE__
			glUnmapBuffer(GL_ARRAY_BUFFER);
#else
			glUnmapBufferARB(GL_ARRAY_BUFFER);
#endif

			glBindBuffer(GL_ARRAY_BUFFER, 0);
#else

			glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, mStride*vcount, mBackingStore, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

#endif
			mLocked = false;
		}
	}

	//private:
	bool         mLocked;
	unsigned int mStride;
	unsigned int mVertexCount;
	GLuint mVertexBuffer;
#if USE_VDO_MAP
#else
	void        *mBackingStore;
#endif
};

class MyIphoneIndexBuffer : public IphoneIndexBuffer
{
public:
	MyIphoneIndexBuffer(const unsigned short *indices, unsigned int icount, bool dynamic)
	{
		mLocked = false;
		unsigned int size = sizeof(unsigned short)*icount;
		mIndexCount = icount;
		mIndexBuffer = 0;
		glGenBuffers(1, &mIndexBuffer);
		if (mIndexBuffer)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mIndexBuffer);
			glBufferData(GL_ARRAY_BUFFER, size, indices, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	~MyIphoneIndexBuffer(void)
	{
		release();
	}

	virtual void release(void)
	{
		if (mIndexBuffer)
		{
			glDeleteBuffers(1, &mIndexBuffer);
			mIndexBuffer = 0;
		}
	}

	virtual void *lock(void)
	{

#define GL_GLEXT_PROTOTYPES 1
		void *ret = 0;
		assert(mLocked == false);
		if (mIndexBuffer && mLocked == false)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mIndexBuffer);

			ret = glMapBufferOESEXT(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			mLocked = true;
		}
		return ret;
	}
	virtual void   unlock(void)
	{
		assert(mLocked == true);
		if (mLocked)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mIndexBuffer);
						
			glUnmapBufferOESEXT(GL_ARRAY_BUFFER);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			mLocked = false;
		}
	}

	//private:
	unsigned int mIndexCount;
	GLuint mIndexBuffer;
	bool mLocked;
};

class MyIphoneGraphics : public IphoneGraphics
{
public:
	MyIphoneGraphics(void)
	{
		mActiveTexture = 0;
		gIphoneGraphics = this;
	}

	~MyIphoneGraphics(void)
	{
		gIphoneGraphics = 0;
	}


	void initExtensions() {

		glGenVertexArraysOESEXT = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
		glBindVertexArrayOESEXT = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
		glDeleteVertexArraysOESEXT = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArraysOES");

		glMapBufferOESEXT = (PFNGLMAPBUFFEROESPROC)eglGetProcAddress("glMapBufferOES");
		glUnmapBufferOESEXT = (PFNGLUNMAPBUFFEROESPROC)eglGetProcAddress("glUnmapBufferOES");
	}

	virtual IphoneTexture * createIphoneTexture(const unsigned char *data, unsigned int width, unsigned int height)
	{
		MyIphoneTexture *m = new MyIphoneTexture(data, width, height);
		return static_cast< IphoneTexture *>(m);
	}

	virtual IphoneVertexBuffer * createIphoneVertexBuffer(unsigned int fvf, const void *vbuffer, unsigned int vcount, bool dynamic)
	{
		MyIphoneVertexBuffer *m = new MyIphoneVertexBuffer(fvf, vbuffer, vcount, dynamic);
		return static_cast< IphoneVertexBuffer *>(m);
	}

	virtual IphoneIndexBuffer  * createIphoneIndexBuffer(const unsigned short *indices, unsigned int icount, bool dynamic)
	{
		MyIphoneIndexBuffer *m = new MyIphoneIndexBuffer(indices, icount, dynamic);
		return static_cast< IphoneIndexBuffer *>(m);
	}

	virtual void                 setActiveTexture(IphoneTexture *texture)
	{
		mActiveTexture = texture;
		// setup texture mapping
		MyIphoneTexture *m = static_cast< MyIphoneTexture *>(texture);
		glEnable(GL_TEXTURE_2D);
		if (m)
			glBindTexture(GL_TEXTURE_2D, m->mTexture);
		else
			glBindTexture(GL_TEXTURE_2D, 0);
	}

	virtual IphoneTexture      * getActiveTexture(void)
	{
		return mActiveTexture;
	}

	virtual void                 renderTriangleList(const glm::mat4 &transform, IphoneVertexBuffer *vb, IphoneIndexBuffer *ib)
	{

		MyIphoneVertexBuffer *mvb = static_cast< MyIphoneVertexBuffer *>(vb);
		MyIphoneIndexBuffer  *mib = static_cast< MyIphoneIndexBuffer *>(ib);

		//glPushMatrix();
		//glMultMatrixf(transform.ptr());

	/*	glDisable(GL_CULL_FACE);

		glBindBuffer(GL_ARRAY_BUFFER, mvb->mVertexBuffer);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, mvb->mStride, 0);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, mvb->mStride, (GLvoid *)12);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mib->mIndexBuffer);
		glDrawElements(GL_TRIANGLES, mib->mIndexCount, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);*/


		//glPopMatrix();
	}

	virtual void renderTriangleList(const glm::mat4 &transform, IphoneVertexBuffer *vb, IphoneIndexBuffer *ib, uint32_t vcount, uint32_t tcount)
	{

		MyIphoneVertexBuffer *mvb = static_cast< MyIphoneVertexBuffer *>(vb);
		MyIphoneIndexBuffer  *mib = static_cast< MyIphoneIndexBuffer *>(ib);

		/*glPushMatrix();
		glMultMatrixf(transform.ptr());

		glDisable(GL_CULL_FACE);

		glBindBuffer(GL_ARRAY_BUFFER, mvb->mVertexBuffer);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, mvb->mStride, 0);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, mvb->mStride, (GLvoid *)12);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mib->mIndexBuffer);

		glDrawElements(GL_TRIANGLES, tcount * 3, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glPopMatrix();*/
	}

	virtual void                 setViewMatrix(const glm::mat4 &view)
	{
		/*glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(view.ptr());*/
	}

	virtual void                 setProjectionMatrix(const glm::mat4 &projection)
	{
		/*glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(projection.ptr());
		glMatrixMode(GL_MODELVIEW);*/
	}

	virtual void setZenable(bool state)
	{
		glDepthMask(state);
		glDepthFunc(GL_LEQUAL);
	}

	virtual void setAlphaTest(bool state, float value)
	{
		if (state)
		{
			//glAlphaFunc(GL_GREATER, value);
			glEnable(GL_ALPHA);
		}
		else
		{
			glDisable(GL_ALPHA);
		}
	}



private:
	IphoneTexture *mActiveTexture;
};


IphoneGraphics * createIphoneGraphics(void)
{
	MyIphoneGraphics *mg = new MyIphoneGraphics;
	return static_cast< IphoneGraphics * >(mg);
}


void     releaseIphoneGraphics(IphoneGraphics *ig)
{
	MyIphoneGraphics *mg = static_cast< MyIphoneGraphics *>(ig);
	delete mg;
}
