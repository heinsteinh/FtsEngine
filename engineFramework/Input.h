#pragma once


#include "Lib.h"
#include "system.h"
#include "taskmanager.h"
#include "VideoSystem.h"

#include "keyboard.h"
#include "TouchCallback.h"
//#include "input/mouse.h"


namespace input
{
	class Win32MsgPump;
	class Input : public core::System
	{
	public:
		typedef std::function<void(int, int)> glfwSetKeyCallback;
		typedef std::shared_ptr<input::Input> InputPtr;
	public:
		Input();
		virtual ~Input();

		virtual bool init();
		virtual void update();
		virtual void shutdown();


		
		void handle(const video::VideoSystem::WindowCreated&);

		const std::shared_ptr<Keyboard>& getKeyboard();
		const std::shared_ptr<TouchCallback>& getTouch();

	protected:
		std::shared_ptr<Keyboard> mKeyboard;
		std::shared_ptr<TouchCallback> mTouch;

		Win32MsgPump*				m_msg_pump;
	};
}
