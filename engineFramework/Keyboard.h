#pragma once


#include "Keys.h"


namespace input 
{

	class Keyboard
	{
	public:
		bool mKeyState[GLFW_KEY_LAST];
		

		Keyboard();
		virtual ~Keyboard();

		static void glfwKeyboardCallback(int key, int state);

		struct KeyPressed 
		{
			int mKey;

			KeyPressed(int key);
		};

		struct KeyReleased
		{
			int mKey;

			KeyReleased(int key);
		};

		void handle(const KeyPressed& kp);
		void handle(const KeyReleased& kp);
	};
}
