#include "stdafx.h"
#include "Joystick.h"

//#define CRAP_PLATFORM_WIN
//
//#if defined( CRAP_PLATFORM_WIN )
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#else
//#include <GL/gl.h>
//#include <GL/glu.h>
//#endif
//
//
//#if defined(CRAP_PLATFORM_WIN)
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glu32.lib")
//#endif



namespace core
{
//https://github.com/stevenblaster/craplib/blob/86d39ce588ea7cc0a17fbc584053bfcb1f011c86/source/craplib/source/opengl/controller.cpp

	joystick::user_joystick_callback_function joystick::_on_attach_function = 0;
	joystick::user_joystick_callback_function joystick::_on_deattach_function = 0;

	joystick::joystick(void)
	{

	}

	joystick::~joystick(void)
	{

	}

	void joystick::poll_events(void)
	{
		for (int i = 0; i < 16; ++i)
		{
		}
	}

	float joystick::get_axis(joy_id joystick_id, axis axis_id)
	{
		return _status[joystick_id].axis_info[axis_id];
	}

	bool joystick::get_button(joy_id joystick_id, button button_id)
	{
		return _status[joystick_id].button_info[button_id] == 1;
	}

	void joystick::set_on_attach_function(void(*function)(joy_id id, joystick_info info))
	{
		_on_attach_function = function;
	}

	void joystick::set_on_deattach_function(void(*function)(joy_id id, joystick_info info))
	{
		_on_deattach_function = function;
	}
}