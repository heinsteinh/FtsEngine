#ifndef OA_WINDOW_H
#define OA_WINDOW_H

#include <string>


class Window {
public:
	friend class Video;

	Window();
	virtual ~Window();

	bool create();
	void destroy();

protected:
	unsigned int mWidth;
	unsigned int mHeight;

	bool mFullScreen;

	unsigned int mRedBits;
	unsigned int mGreenBits;
	unsigned int mBlueBits;
	unsigned int mAlphaBits;

	unsigned int mDepthBits;
	unsigned int mStencilBits;

	std::string mTitle;
};

#endif
