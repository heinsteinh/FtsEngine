#include "stdafx.h"
#include "Keyboard.h"

#include "eventhandler.h"
#include "eventchannel.h"

#include <iostream>
#include <cassert>

namespace input 
{
	Keyboard::Keyboard()
	{
		core::EventChannel chan;

		chan.add<KeyPressed>(*this);
		chan.add<KeyReleased>(*this);

		for (int i = 0; i < GLFW_KEY_LAST; ++i)
			mKeyState[i] = false;
	}

	Keyboard::~Keyboard() {
	}

	Keyboard::KeyPressed::KeyPressed(int key) : mKey(key) {}
	Keyboard::KeyReleased::KeyReleased(int key) : mKey(key) {}

	void Keyboard::glfwKeyboardCallback(int key, int state)
	{
		static core::EventChannel chan;

		switch (state){
		case GLFW_PRESS:
			chan.broadcast(KeyPressed(key));
			break;

		case GLFW_RELEASE:
			chan.broadcast(KeyReleased(key));
			break;

		default:
			std::cout << "unhandled glfw keystate?" << std::endl;
			break;
		}
	}

	void Keyboard::handle(const KeyPressed& kp)
	{
		assert(kp.mKey < GLFW_KEY_LAST);

		mKeyState[kp.mKey] = true;
	}

	void Keyboard::handle(const KeyReleased& kr) {
		assert(kr.mKey < GLFW_KEY_LAST);

		mKeyState[kr.mKey] = false;
	}
}
