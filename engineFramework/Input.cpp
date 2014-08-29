#include "stdafx.h"
#include "Input.h"
#include "eventchannel.h"
#include "Engine.h"

#include <Windows.h>



namespace input
{

	class Win32MsgPump 
	{
	public:
		bool message_pump()
		{
			MSG msg;
			while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					return false;
				}
				

				TranslateMessage(&msg);
				DispatchMessage(&msg);


			}

			return true;
		}
	};

	Input::Input() :core::System("Input", core::Task::NONE), mTouch(new TouchCallback()), mKeyboard(new Keyboard())
	{
		enableUpdater();
		core::EventChannel chan;
		chan.add<video::VideoSystem::WindowCreated>(*this);
	}

	Input::~Input()
	{
	}


	bool Input::init() 
	{
		m_msg_pump = new Win32MsgPump;

		
		return true;
	}


	void Input::update()
	{
		//m_msg_pump->message_pump();

		
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		
		
		}



		/*if (GetAsyncKeyState(VK_UP))
		{
			core::EventChannel evt;
			evt.broadcast(Keyboard::KeyPressed(VK_UP));
		}
		
		if (GetAsyncKeyState(VK_DOWN))
		{
			core::EventChannel evt;
			evt.broadcast(Keyboard::KeyPressed(VK_DOWN));
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			core::EventChannel evt;
			evt.broadcast(Keyboard::KeyPressed(VK_RIGHT));
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			core::EventChannel evt;
			evt.broadcast(Keyboard::KeyPressed(VK_LEFT));
		}


		if (GetAsyncKeyState(VK_F2))
		{
			core::EventChannel evt;
			evt.broadcast(Keyboard::KeyPressed(VK_F2));
		}

		if (GetAsyncKeyState(VK_F1))
		{
			core::EventChannel evt;
			evt.broadcast(Keyboard::KeyPressed(VK_F1));
		}*/



		if (msg.message == WM_QUIT)
		{
			mEngine->stop();
		}

	}

	void Input::handle(const video::VideoSystem::WindowCreated&)
	{
		
		glfwSetKeyCallback(&mKeyboard->glfwKeyboardCallback);	

	}

	void Input::shutdown()
	{
		glfwSetKeyCallback();

		
		delete m_msg_pump;
		m_msg_pump = NULL;
	}


	const std::shared_ptr<Keyboard>& Input::getKeyboard()
	{
		return mKeyboard;
	}


	const std::shared_ptr<TouchCallback>& Input::getTouch()
	{
		return mTouch;
	}


	
}
