#pragma once 

#include <stdint.h>
//https://github.com/stevenblaster/craplib/blob/86d39ce588ea7cc0a17fbc584053bfcb1f011c86/source/craplib/include/opengl/keyboard.h

namespace input
{


	enum {
		//############################################################################
		//# Input handling definitions
		//############################################################################

		//# Key and button state / action definitions

		GLFW_RELEASE = 0,
		GLFW_PRESS = 1,

		//# Keyboard key definitions : 8 - bit ISO - 8859 - 1 (Latin 1) encoding is used
		//# for printable keys(such as A - Z, 0 - 9 etc), and values above 256
		//# represent special(non - printable) keys(e.g.F1, Page Up etc).
		GLFW_KEY_UNKNOWN = -1,
		GLFW_KEY_SPACE = 32,
		GLFW_KEY_SPECIAL = 256,
		GLFW_KEY_ESC = GLFW_KEY_SPECIAL + 1,
		GLFW_KEY_F1 = GLFW_KEY_SPECIAL + 2,
		GLFW_KEY_F2 = GLFW_KEY_SPECIAL + 3,
	/*	GLFW_KEY_F3 = GLFW_KEY_SPECIAL + 4
		GLFW_KEY_F4 = GLFW_KEY_SPECIAL + 5
		GLFW_KEY_F5 = GLFW_KEY_SPECIAL + 6
		GLFW_KEY_F6 = GLFW_KEY_SPECIAL + 7
		GLFW_KEY_F7 = GLFW_KEY_SPECIAL + 8
		GLFW_KEY_F8 = GLFW_KEY_SPECIAL + 9
		GLFW_KEY_F9 = GLFW_KEY_SPECIAL + 10
		GLFW_KEY_F10 = GLFW_KEY_SPECIAL + 11
		GLFW_KEY_F11 = GLFW_KEY_SPECIAL + 12
		GLFW_KEY_F12 = GLFW_KEY_SPECIAL + 13
		GLFW_KEY_F13 = GLFW_KEY_SPECIAL + 14
		GLFW_KEY_F14 = GLFW_KEY_SPECIAL + 15
		GLFW_KEY_F15 = GLFW_KEY_SPECIAL + 16
		GLFW_KEY_F16 = GLFW_KEY_SPECIAL + 17
		GLFW_KEY_F17 = GLFW_KEY_SPECIAL + 18
		GLFW_KEY_F18 = GLFW_KEY_SPECIAL + 19
		GLFW_KEY_F19 = GLFW_KEY_SPECIAL + 20
		GLFW_KEY_F20 = GLFW_KEY_SPECIAL + 21
		GLFW_KEY_F21 = GLFW_KEY_SPECIAL + 22
		GLFW_KEY_F22 = GLFW_KEY_SPECIAL + 23
		GLFW_KEY_F23 = GLFW_KEY_SPECIAL + 24
		GLFW_KEY_F24 = GLFW_KEY_SPECIAL + 25
		GLFW_KEY_F25 = GLFW_KEY_SPECIAL + 26
		GLFW_KEY_UP = GLFW_KEY_SPECIAL + 27
		GLFW_KEY_DOWN = GLFW_KEY_SPECIAL + 28
		GLFW_KEY_LEFT = GLFW_KEY_SPECIAL + 29
		GLFW_KEY_RIGHT = GLFW_KEY_SPECIAL + 30
		GLFW_KEY_LSHIFT = GLFW_KEY_SPECIAL + 31
		GLFW_KEY_RSHIFT = GLFW_KEY_SPECIAL + 32
		GLFW_KEY_LCTRL = GLFW_KEY_SPECIAL + 33
		GLFW_KEY_RCTRL = GLFW_KEY_SPECIAL + 34
		GLFW_KEY_LALT = GLFW_KEY_SPECIAL + 35
		GLFW_KEY_RALT = GLFW_KEY_SPECIAL + 36
		GLFW_KEY_TAB = GLFW_KEY_SPECIAL + 37
		GLFW_KEY_ENTER = GLFW_KEY_SPECIAL + 38
		GLFW_KEY_BACKSPACE = GLFW_KEY_SPECIAL + 39
		GLFW_KEY_INSERT = GLFW_KEY_SPECIAL + 40
		GLFW_KEY_DEL = GLFW_KEY_SPECIAL + 41
		GLFW_KEY_PAGEUP = GLFW_KEY_SPECIAL + 42
		GLFW_KEY_PAGEDOWN = GLFW_KEY_SPECIAL + 43
		GLFW_KEY_HOME = GLFW_KEY_SPECIAL + 44
		GLFW_KEY_END = GLFW_KEY_SPECIAL + 45
		GLFW_KEY_KP_0 = GLFW_KEY_SPECIAL + 46
		GLFW_KEY_KP_1 = GLFW_KEY_SPECIAL + 47
		GLFW_KEY_KP_2 = GLFW_KEY_SPECIAL + 48
		GLFW_KEY_KP_3 = GLFW_KEY_SPECIAL + 49
		GLFW_KEY_KP_4 = GLFW_KEY_SPECIAL + 50
		GLFW_KEY_KP_5 = GLFW_KEY_SPECIAL + 51
		GLFW_KEY_KP_6 = GLFW_KEY_SPECIAL + 52
		GLFW_KEY_KP_7 = GLFW_KEY_SPECIAL + 53
		GLFW_KEY_KP_8 = GLFW_KEY_SPECIAL + 54
		GLFW_KEY_KP_9 = GLFW_KEY_SPECIAL + 55
		GLFW_KEY_KP_DIVIDE = GLFW_KEY_SPECIAL + 56
		GLFW_KEY_KP_MULTIPLY = GLFW_KEY_SPECIAL + 57
		GLFW_KEY_KP_SUBTRACT = GLFW_KEY_SPECIAL + 58
		GLFW_KEY_KP_ADD = GLFW_KEY_SPECIAL + 59
		GLFW_KEY_KP_DECIMAL = GLFW_KEY_SPECIAL + 60
		GLFW_KEY_KP_EQUAL = GLFW_KEY_SPECIAL + 61
		GLFW_KEY_KP_ENTER = GLFW_KEY_SPECIAL + 62*/
		GLFW_KEY_LAST = GLFW_KEY_F2
	};
	enum KeyType
	{
		KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN,
		KEY_RSHIFT, KEY_LSHIFT,
		KEY_RCTRL, KEY_LCTRL,
		KEY_RALT, KEY_LALT,
		KEY_RETURN,

		KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
		KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

		KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
	};

	namespace term
	{
		struct resize_event
		{
			int width, height;
			int delta_width, delta_height;
		};

		enum class key
		{
			f1 = 0xFFFF - 0,
			f2 = 0xFFFF - 1,
			f3 = 0xFFFF - 2,
			f4 = 0xFFFF - 3,
			f5 = 0xFFFF - 4,
			f6 = 0xFFFF - 5,
			f7 = 0xFFFF - 6,
			f8 = 0xFFFF - 7,
			f9 = 0xFFFF - 8,
			f10 = 0xFFFF - 9,
			f11 = 0xFFFF - 10,
			f12 = 0xFFFF - 11,
			insert = 0xFFFF - 12,
			del = 0xFFFF - 13,
			home = 0xFFFF - 14,
			end = 0xFFFF - 15,
			pgup = 0xFFFF - 16,
			pgdn = 0xFFFF - 17,
			arrow_up = 0xFFFF - 18,
			arrow_down = 0xFFFF - 19,
			arrow_left = 0xFFFF - 20,
			arrow_right = 0xFFFF - 21,

			ctrl_tilde = 0x00,
			ctrl_2 = 0x00, /* Clashes with ctrl_tilde */
			ctrl_a = 0x01,
			ctrl_b = 0x02,
			ctrl_c = 0x03,
			ctrl_d = 0x04,
			ctrl_e = 0x05,
			ctrl_f = 0x06,
			ctrl_g = 0x07,
			backspace = 0x08,
			ctrl_h = 0x08, /* Clashes with ctrl_backspace */
			tab = 0x09,
			ctrl_i = 0x09, /* Clashes with tab */
			ctrl_j = 0x0A,
			ctrl_k = 0x0B,
			ctrl_l = 0x0C,
			enter = 0x0D,
			ctrl_m = 0x0D, /* Clashes with enter */
			ctrl_n = 0x0E,
			ctrl_o = 0x0F,
			ctrl_p = 0x10,
			ctrl_q = 0x11,
			ctrl_r = 0x12,
			ctrl_s = 0x13,
			ctrl_t = 0x14,
			ctrl_u = 0x15,
			ctrl_v = 0x16,
			ctrl_w = 0x17,
			ctrl_x = 0x18,
			ctrl_y = 0x19,
			ctrl_z = 0x1A,
			escape = 0x1B,
			ctrl_lsq_bracket = 0x1B, /* Clashes with esc */
			ctrl_3 = 0x1B, /* Clashes with esc */
			ctrl_4 = 0x1C,
			ctrl_backslash = 0x1C, /* Clashes with ctrl_4 */
			ctrl_5 = 0x1D,
			ctrl_rsq_bracket = 0x1D, /* Clashes with ctrl_5 */
			ctrl_6 = 0x1E,
			ctrl_7 = 0x1F,
			ctrl_slash = 0x1F, /* Clashes with ctrl_7 */
			ctrl_underscore = 0x1F, /* Clashes with ctrl_7 */
			space = 0x20,
			backspace2 = 0x7F,
			ctrl_8 = 0x7F /* Clashes with delete */
		};

		enum class modifier
		{
			alt
		};

		/* If the unicode char is null, the value is
		* represented as a key code. */
		struct key_event
		{
			key k;
			//unicode_t ch;
			modifier mod;
		};
	}
};