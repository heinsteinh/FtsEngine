/*
* Includes all relevant libraries
*/

#ifndef OA_LIBS_H
#define OA_LIBS_H


#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <unordered_map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <ostream>
#include <strstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>

#include <thread>
#include <future>
#include <functional>

#define GLM_FORCE_RADIANS //GLM: perspective function taking degrees as a parameter is deprecated. #define GLM_FORCE_RADIANS before including GLM headers to remove this message.
#include <glm/glm.hpp>
#include <glm/ext.hpp>



//#define GLM_FORCE_CXX11
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>
//#include <glm/gtc/matrix_access.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/string_cast.hpp>



#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")


#define STRINGIFY(A)  #A

enum
{
	ATTRIB_VERTEX,
	ATTRIB_NORMAL,
	ATTRIB_TEXTURE_UV,
	NUM_ATTRIBUTES
};


enum
{
	UNIFORM_MODELVIEWPROJECTION_MATRIX,
	UNIFORM_MODEL_MATRIX,
	UNIFORM_LIGHT_VECTOR,
	UNIFORM_TEXTURE_0,
	NUM_UNIFORMS
};


#define GL_CHECK_ \
		{ \
		GLenum glError = glGetError(); \
if (glError != GL_NO_ERROR) {\
printf("glGetError() = %i (0x%.8x) at line %i\n", glError, glError, __LINE__); \
}\
else{\
		printf("gl process ok at line %i\n", __LINE__); \
} \
		}


#define GL_CHECK \
	{ \
	GLenum glError = glGetError(); \
		if (glError != GL_NO_ERROR) {\
			printf("glGetError() = %i (0x%.8x) at line %i\n", glError, glError, __LINE__); \
			assert(false); \
		} \
	}


// Bring common functions from C into global namespace
using std::memcpy;
using std::fabs;
using std::sqrt;
using std::cos;
using std::sin;
using std::tan;
//using std::isspace;
//using std::isdigit;
//using std::toupper;
//using std::tolower;
using std::size_t;
using std::min;
using std::max;
using std::modf;
using std::atoi;

// Common
#ifndef NULL
#define NULL 0
#endif


// Object deletion macro
#define SAFE_DELETE(x) \
{ \
	delete x; \
	x = NULL; \
		}

// Array deletion macro
#define SAFE_DELETE_ARRAY(x) \
{ \
	delete[] x; \
	x = NULL; \
	}

// Ref cleanup macro
#define SAFE_RELEASE(x) \
if (x) \
{ \
	(x)->release(); \
	x = NULL; \
}


/**
* GL assertion that can be used for any OpenGL function call.
*
* This macro will assert if an error is detected when executing
* the specified GL code. This macro will do nothing in release
* mode and is therefore safe to use for realtime/per-frame GL
* function calls.
*/
#ifdef NDEBUG
#define GL_ASSERT( gl_code ) gl_code
#else
#define GL_ASSERT( gl_code ) do \
{ \
	gl_code; \
	__gl_error_code = glGetError(); \
	GP_ASSERT(__gl_error_code == GL_NO_ERROR); \
} while (0)
#endif


// Graphics (OpenGL)
#ifdef __QNX__
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <screen/screen.h>
extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays;
extern PFNGLISVERTEXARRAYOESPROC glIsVertexArray;
#define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#define glClearDepth glClearDepthf
#define OPENGL_ES
#define USE_PVRTC
#ifdef __arm__
#define USE_NEON
#endif
#elif __ANDROID__
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays;
extern PFNGLISVERTEXARRAYOESPROC glIsVertexArray;
#define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#define glClearDepth glClearDepthf
#define OPENGL_ES
#elif WIN32
#define OPENGL_ES
#define USE_VAO


#define glClearDepth glClearDepthf
#define GL_BGRA GL_BGRA_EXT

#define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#define GL_WRITE_ONLY GL_WRITE_ONLY_OES

#include <EGL/egl.h>
//#include <screen/screen.h>

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



#elif __linux__
#define GLEW_STATIC
#include <GL/glew.h>
#define USE_VAO
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#define glBindVertexArray glBindVertexArrayOES
#define glDeleteVertexArrays glDeleteVertexArraysOES
#define glGenVertexArrays glGenVertexArraysOES
#define glIsVertexArray glIsVertexArrayOES
#define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#define glClearDepth glClearDepthf
#define OPENGL_ES
#define USE_VAO
#ifdef __arm__
#define USE_NEON
#endif
#elif TARGET_OS_MAC
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#define glBindVertexArray glBindVertexArrayAPPLE
#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glIsVertexArray glIsVertexArrayAPPLE
#define USE_VAO
#else
#error "Unsupported Apple Device"
#endif
#endif




#endif

