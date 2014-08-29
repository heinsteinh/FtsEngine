#pragma once


#include <string>
#include <cstdint>
#include <memory>



namespace GameScene
{
	class SceneBase;
}

namespace core
{

	typedef std::shared_ptr<GameScene::SceneBase> SceneBasePtr;
	class  Window 
	{
	public:
		friend class Video;
		typedef std::shared_ptr<core::Window> WindowPtr;

		enum eWindowType : std::uint8_t 
		{
			GLFW = 0,
			QT = 1
		};

		Window(const std::string& title, eWindowType type) 
			: mTitle(title)
			, mWindowType(type)
			, mIsClose(false)
			, mWidth(320)
			, mHeight(480)
			, mTimeElapsedSinceLastFrame(0.0) {}
		
		virtual ~Window() {}



		const eWindowType& type() { return mWindowType; }
		virtual bool isClosed() { return mIsClose; };


		virtual void render(double) = 0;
		virtual void update(double) = 0;
		virtual bool create() = 0;
		virtual void destroy() = 0;

				
		int GetWidth() { return mWidth; }
		int GetHeight(){ return mHeight; }

		float GetWindowAspectRatio() { return (float)((float)mWidth / (float)mHeight); };


		int								mWidth;
		int								mHeight;
		bool							mFullScreen;
		bool							mAutoSizeWindow;

		double							mTimeElapsedSinceLastFrame;
		std::string						mTitle;

	protected:
		SceneBasePtr					mActiveScene;


	private:
		eWindowType						mWindowType;
		bool							mIsClose;	

	};

}