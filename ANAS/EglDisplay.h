#pragma once

#include "Libs.h"
#include "Logger.h"


namespace ANAS
{
	

#define SHADER_SOURCE(...) #__VA_ARGS__

	class EglDisplay
	{
	protected:
		EglDisplay();

	public:
		static bool InitTestWindow();
		static bool DestroyTestWindow();
		static bool ReizeWindow(int width, int height);
		static EGLNativeWindowType GetNativeWindow();

	protected:
		virtual void Init();
		virtual void ShutDown();

		virtual void swapBuffers();
		static void drawQuad(GLuint program, const std::string& positionAttribName, GLfloat quadDepth);
		static GLuint compileShader(GLenum type, const std::string &source);
		static GLuint compileProgram(const std::string &vsSource, const std::string &fsSource);
		static bool extensionEnabled(const std::string &extName);

		void setClientVersion(int clientVersion);
		void setWindowWidth(int width);
		void setWindowHeight(int height);
		void setConfigRedBits(int bits);
		void setConfigGreenBits(int bits);
		void setConfigBlueBits(int bits);
		void setConfigAlphaBits(int bits);
		void setConfigDepthBits(int bits);
		void setConfigStencilBits(int bits);
		void setMultisampleEnabled(bool enabled);
		
		int getClientVersion() const;
		int getWindowWidth() const;
		int getWindowHeight() const;
		int getConfigRedBits() const;
		int getConfigGreenBits() const;
		int getConfigBlueBits() const;
		int getConfigAlphaBits() const;
		int getConfigDepthBits() const;
		int getConfigStencilBits() const;
		bool isMultisampleEnabled() const;

		virtual void Render() = 0;

	private:
		bool createEGLContext();
		bool destroyEGLContext();

		int mClientVersion;
		int mWidth;
		int mHeight;
		int mRedBits;
		int mGreenBits;
		int mBlueBits;
		int mAlphaBits;
		int mDepthBits;
		int mStencilBits;
		bool mMultisample;

		EGLConfig mConfig;
		EGLSurface mSurface;
		EGLContext mContext;

		static EGLDisplay mDisplay;
		static EGLNativeWindowType mNativeWindow;
		static EGLNativeDisplayType mNativeDisplay;
	};


	class ANGLETestEnvironment 
	{
	public:
		ANGLETestEnvironment(){}
		virtual ~ANGLETestEnvironment(){}
		virtual void InitUp();
		virtual void ShutDown();
	};
	
}