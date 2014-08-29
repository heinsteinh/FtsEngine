#include "stdafx.h"
#include "EglDisplay.h"


//https://chromium.googlesource.com/angle/angle/+/testbranchthree/tests/angle_tests/ANGLETest.cpp

namespace ANAS
{

	EGLDisplay EglDisplay::mDisplay = 0;
	EGLNativeWindowType EglDisplay::mNativeWindow = 0;
	EGLNativeDisplayType EglDisplay::mNativeDisplay = 0;

	EglDisplay::EglDisplay() :
		
		mClientVersion(2),
		mWidth(1280),
		mHeight(720),
		mRedBits(-1),
		mGreenBits(-1),
		mBlueBits(-1),
		mAlphaBits(-1),
		mDepthBits(-1),
		mStencilBits(-1),
		mMultisample(false)
	{
	}

	void EglDisplay::Init()
	{

		ReizeWindow(mWidth, mHeight);

		if (!createEGLContext())
		{
			gLog.error() << "egl context creation failed.";
		}
	}

	void EglDisplay::ShutDown()
	{		
		if (!destroyEGLContext())
		{
			gLog.error() << "egl context destruction failed.";
		}
	}

	void EglDisplay::swapBuffers()
	{

		eglSwapBuffers(mDisplay, mSurface);
		GL_CHECK
	}


	void EglDisplay::drawQuad(GLuint program, const std::string& positionAttribName, GLfloat quadDepth)
	{
		GLint positionLocation = glGetAttribLocation(program, positionAttribName.c_str());
		glUseProgram(program);
		const GLfloat vertices[] =
		{
			-1.0f, 1.0f, quadDepth,
			-1.0f, -1.0f, quadDepth,
			1.0f, -1.0f, quadDepth,
			-1.0f, 1.0f, quadDepth,
			1.0f, -1.0f, quadDepth,
			1.0f, 1.0f, quadDepth,
		};
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(positionLocation);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(positionLocation);
		glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glUseProgram(0);
	}
	GLuint EglDisplay::compileShader(GLenum type, const std::string &source)
	{
		GLuint shader = glCreateShader(type);
		const char *sourceArray[1] = { source.c_str() };
		glShaderSource(shader, 1, sourceArray, NULL);
		glCompileShader(shader);
		GLint compileResult;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
		if (compileResult == 0)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::vector<GLchar> infoLog(infoLogLength);
			glGetShaderInfoLog(shader, infoLog.size(), NULL, infoLog.data());
			std::cerr << "shader compilation failed: " << infoLog.data();
			glDeleteShader(shader);
			shader = 0;
		}
		return shader;
	}
	GLuint EglDisplay::compileProgram(const std::string &vsSource, const std::string &fsSource)
	{
		GLuint program = glCreateProgram();
		GLuint vs = compileShader(GL_VERTEX_SHADER, vsSource);
		GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSource);
		if (vs == 0 || fs == 0)
		{
			glDeleteShader(fs);
			glDeleteShader(vs);
			glDeleteProgram(program);
			return 0;
		}
		glAttachShader(program, vs);
		glDeleteShader(vs);
		glAttachShader(program, fs);
		glDeleteShader(fs);
		glLinkProgram(program);
		GLint linkStatus;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == 0)
		{
			GLint infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::vector<GLchar> infoLog(infoLogLength);
			glGetProgramInfoLog(program, infoLog.size(), NULL, infoLog.data());
			std::cerr << "program link failed: " << infoLog.data();
			glDeleteProgram(program);
			return 0;
		}
		return program;
	}

	bool EglDisplay::extensionEnabled(const std::string &extName)
	{
		const char* extString = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
		return strstr(extString, extName.c_str()) != NULL;
	}
	void EglDisplay::setClientVersion(int clientVersion)
	{
		mClientVersion = clientVersion;
	}
	void EglDisplay::setWindowWidth(int width)
	{
		mWidth = width;
	}
	void EglDisplay::setWindowHeight(int height)
	{
		mHeight = height;
	}
	void EglDisplay::setConfigRedBits(int bits)
	{
		mRedBits = bits;
	}
	void EglDisplay::setConfigGreenBits(int bits)
	{
		mGreenBits = bits;
	}
	void EglDisplay::setConfigBlueBits(int bits)
	{
		mBlueBits = bits;
	}
	void EglDisplay::setConfigAlphaBits(int bits)
	{
		mAlphaBits = bits;
	}
	void EglDisplay::setConfigDepthBits(int bits)
	{
		mDepthBits = bits;
	}
	void EglDisplay::setConfigStencilBits(int bits)
	{
		mStencilBits = bits;
	}
	void EglDisplay::setMultisampleEnabled(bool enabled)
	{
		mMultisample = enabled;
	}
	int EglDisplay::getClientVersion() const
	{
		return mClientVersion;
	}
	int EglDisplay::getWindowWidth() const
	{
		return mWidth;
	}
	int EglDisplay::getWindowHeight() const
	{
		return mHeight;
	}
	int EglDisplay::getConfigRedBits() const
	{
		return mRedBits;
	}
	int EglDisplay::getConfigGreenBits() const
	{
		return mGreenBits;
	}
	int EglDisplay::getConfigBlueBits() const
	{
		return mBlueBits;
	}
	int EglDisplay::getConfigAlphaBits() const
	{
		return mAlphaBits;
	}
	int EglDisplay::getConfigDepthBits() const
	{
		return mDepthBits;
	}
	int EglDisplay::getConfigStencilBits() const
	{
		return mStencilBits;
	}
	bool EglDisplay::isMultisampleEnabled() const
	{
		return mMultisample;
	}
	bool EglDisplay::createEGLContext()
	{
		const EGLint configAttributes[] =
		{
			EGL_RED_SIZE, (mRedBits >= 0) ? mRedBits : EGL_DONT_CARE,
			EGL_GREEN_SIZE, (mGreenBits >= 0) ? mGreenBits : EGL_DONT_CARE,
			EGL_BLUE_SIZE, (mBlueBits >= 0) ? mBlueBits : EGL_DONT_CARE,
			EGL_ALPHA_SIZE, (mAlphaBits >= 0) ? mAlphaBits : EGL_DONT_CARE,
			EGL_DEPTH_SIZE, (mDepthBits >= 0) ? mDepthBits : EGL_DONT_CARE,
			EGL_STENCIL_SIZE, (mStencilBits >= 0) ? mStencilBits : EGL_DONT_CARE,
			EGL_SAMPLE_BUFFERS, mMultisample ? 1 : 0,
			EGL_NONE
		};

		EGLint configCount;
		if (!eglChooseConfig(mDisplay, configAttributes, &mConfig, 1, &configCount) || (configCount != 1))
		{
			destroyEGLContext();
			return false;
		}
		eglGetConfigAttrib(mDisplay, mConfig, EGL_RED_SIZE, &mRedBits);
		eglGetConfigAttrib(mDisplay, mConfig, EGL_GREEN_SIZE, &mGreenBits);
		eglGetConfigAttrib(mDisplay, mConfig, EGL_BLUE_SIZE, &mBlueBits);
		eglGetConfigAttrib(mDisplay, mConfig, EGL_ALPHA_SIZE, &mBlueBits);
		eglGetConfigAttrib(mDisplay, mConfig, EGL_DEPTH_SIZE, &mDepthBits);
		eglGetConfigAttrib(mDisplay, mConfig, EGL_STENCIL_SIZE, &mStencilBits);
		EGLint samples;
		eglGetConfigAttrib(mDisplay, mConfig, EGL_SAMPLE_BUFFERS, &samples);
		mMultisample = (samples != 0);
		mSurface = eglCreateWindowSurface(mDisplay, mConfig, mNativeWindow, NULL);
		if (mSurface == EGL_NO_SURFACE)
		{
			eglGetError(); // Clear error
			mSurface = eglCreateWindowSurface(mDisplay, mConfig, NULL, NULL);
		}
		if (eglGetError() != EGL_SUCCESS)
		{
			destroyEGLContext();
			return false;
		}
		EGLint contextAttibutes[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, mClientVersion,
			EGL_NONE
		};
	
		mContext = eglCreateContext(mDisplay, mConfig, NULL, contextAttibutes);
		if (eglGetError() != EGL_SUCCESS)
		{
			destroyEGLContext();
			return false;
		}
		eglMakeCurrent(mDisplay, mSurface, mSurface, mContext);
		if (eglGetError() != EGL_SUCCESS)
		{
			destroyEGLContext();
			return false;
		}

		GLubyte* version = (GLubyte*)glGetString(GL_VERSION);
		printf("gl version:%s\n", version);
		const char* eglClient = eglQueryString(mDisplay, EGL_CLIENT_APIS);
		printf("egl client api:%s\n", eglClient);
		GLubyte* vendorName = (GLubyte*)glGetString(GL_VENDOR);
		printf("verdor name:%s\n", vendorName);

		return true;
	}

	bool EglDisplay::destroyEGLContext()
	{
		eglDestroySurface(mDisplay, mSurface);
		eglDestroyContext(mDisplay, mContext);
		return true;
	}


	void ANGLETestEnvironment::InitUp()
	{
		if (!EglDisplay::InitTestWindow())
		{
			gLog.error() << "Failed to create ANGLE test window.";
		}		
	}


	void ANGLETestEnvironment::ShutDown()
	{
		EglDisplay::DestroyTestWindow();
	}
}
	 