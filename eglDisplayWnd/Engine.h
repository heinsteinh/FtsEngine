#pragma once
#include <cstdio>
#include <memory>



//#define RELEASE_BUILD

#ifndef WIN32
#define _ANDROID
#endif

#ifdef _ANDROID

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/log.h>
#ifndef RELEASE_BUILD
#define LOG_TAG "GAME"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#define LOGI //
#define LOGE //
#endif
#else

#ifdef _WIN32

#include <GLES2\gl2.h>

#ifndef RELEASE_BUILD
#define LOGI(...) printf(__VA_ARGS__)
#define LOGE(...) printf(__VA_ARGS__)
#else
#define LOGI //
#define LOGE //
#endif

#endif
#endif

#define GL_CHECK \
{ \
GLenum glError = glGetError(); \
if (glError != GL_NO_ERROR) {\
	printf("glGetError() = %i (0x%.8x) at line %i\n", glError, glError, __LINE__); \
	assert(false); \
} \
}


#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <memory>


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#pragma comment(lib,"libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")


#define _STRINGIFY(a) # a
#define STRINGIFY(a) _STRINGIFY(a)

#include "TGA.h"

//#define SCREEN_W 800
//#define SCREEN_H 480

#define SCREEN_W 640
#define SCREEN_H 480

//const unsigned int uiWidth = 640;
//const unsigned int uiHeight = 480;


#define SAFE_DEL(p) if (p) delete p; p = 0;
#define SAFE_DEL_ARRAY(p) if (p) delete []p; p = 0;

#include <string>
struct DATA_LINE
{
	std::string key;
	std::string value;
};