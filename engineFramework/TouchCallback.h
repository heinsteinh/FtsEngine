#pragma once

#include "WindowVideo.h"
#include <functional>
#include <vector>


//http://code.google.com/p/gdk/source/browse/trunk/Source/Gdk/Input/Touch.h?r=14

namespace input
{

	// Closely match UITouchEvent from the iPhone SDK
	struct TouchEvent 
	{
		typedef enum {
			BEGAN, // whenever a finger touches the surface.
			MOVED, // whenever a finger moves on the surface.
			STATIONARY, // whenever a finger is touching the surface but hasn't moved since the previous event.
			ENDED, // whenever a finger leaves the surface.
			CANCELLED // whenever a touch doesn't end but we need to stop tracking (e.g. putting device to face)
		} Phase;

		double timestamp;
		Phase phase;
		int tapCount;
		float screenX, screenY;
		float previousX, previousY;
	};




	//https://github.com/brackeen/ok-sprites/blob/1a666fdafbfa3b49a6ab5f653a8167ddb6e5099d/src/View.cpp
	//http://code.google.com/p/overdriveassault/source/browse/working/input/mouse.cpp

	class TouchCallback
	{
	public:
		typedef std::function<void(const core::Window::WindowPtr&, const TouchEvent&)> touches_t;
		//typedef std::function<void(const TouchEvent&)> touches_t;


	public:
		int mX;
		int mY;

		TouchEvent mEvt;

	public:
		TouchCallback();
		~TouchCallback();


		touches_t touchesBegan_;
		touches_t touchesEnded_;
		touches_t touchesMoved_;

		
		struct onTouchMoveEntered {};
		struct onTouchMoveExited {};
		struct onTouchCancelled {};
					
		struct touchBegin
		{
			TouchEvent mEvent;

			touchBegin(const TouchEvent& evt);
		};

		struct touchMoved
		{
			TouchEvent mEvent;

			touchMoved(const TouchEvent& evt);
		};

		struct touchEnd
		{
			TouchEvent mEvent;

			touchEnd(const TouchEvent& evt);
		};
		struct touchCancelled
		{
			TouchEvent mEvent;

			touchCancelled(const TouchEvent& evt);
		};
		
		
		static void TouchPosCallback_evt(const TouchEvent&);


		void handle(const TouchCallback::touchMoved& tm);
		void handle(const TouchCallback::touchBegin& tm);
		void handle(const TouchCallback::touchEnd& tm);
		void handle(const TouchCallback::touchCancelled& tm);

	

		
	};

}