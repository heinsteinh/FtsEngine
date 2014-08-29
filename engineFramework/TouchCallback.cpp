#include "stdafx.h"
#include "TouchCallback.h"
#include "eventhandler.h"
#include "eventchannel.h"
#include <iostream>

namespace input
{


	TouchCallback::TouchCallback()
	{
		core::EventChannel chan;

		chan.add<touchBegin>(*this);
		chan.add<touchMoved>(*this);
		chan.add<touchEnd>(*this);
		chan.add<touchCancelled>(*this);
	}


	TouchCallback::~TouchCallback()
	{
	}



	TouchCallback::touchMoved::touchMoved(const TouchEvent& evt) : mEvent(evt) {}
	TouchCallback::touchBegin::touchBegin(const TouchEvent& evt) : mEvent(evt) {}	
	TouchCallback::touchEnd::touchEnd(const TouchEvent& evt) : mEvent(evt) {}
	TouchCallback::touchCancelled::touchCancelled(const TouchEvent& evt) : mEvent(evt) {}



	void TouchCallback::TouchPosCallback_evt(const TouchEvent& evtTouch)
	{
		static core::EventChannel chan;

		switch (evtTouch.phase)
		{
		case TouchEvent::BEGAN:
			chan.broadcast(touchBegin(evtTouch));
			break;

		case TouchEvent::MOVED:
			chan.broadcast(touchMoved(evtTouch));
			break;

		case TouchEvent::ENDED:
			chan.broadcast(touchEnd(evtTouch));
			break;

		case TouchEvent::CANCELLED:
			chan.broadcast(touchCancelled(evtTouch));
			break;

		default:
			std::cout << "unhandled touchCallback inputState?" << std::endl;
			break;
		};
	}


	void TouchCallback::handle(const TouchCallback::touchBegin& tm)
	{
		mEvt = tm.mEvent;
	}

	void TouchCallback::handle(const TouchCallback::touchEnd& tm)
	{
		mEvt = tm.mEvent;
	}

	void TouchCallback::handle(const TouchCallback::touchMoved& tm)
	{
		mEvt = tm.mEvent;
	}

	void TouchCallback::handle(const TouchCallback::touchCancelled& tm)
	{
		mEvt = tm.mEvent;
	}

	
	
}