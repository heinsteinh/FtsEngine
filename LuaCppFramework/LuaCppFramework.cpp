// LuaCppFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


//http://www.jeremyong.com/blog/2014/01/10/interfacing-lua-with-templates-in-c-plus-plus-11/
//https://github.com/jeremyong/Selene

#pragma once
#include <string>
#include <cassert>






#include "Options.h"


// Include the lua headers (the extern "C" is a requirement because we're
// using C++ and lua has been compiled as C code)
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}




#pragma comment(lib,"lua52.lib")




int _tmain(int argc, _TCHAR* argv[])
{

	
		lua_State *l = luaL_newstate();
		luaL_dofile(l, "example.lua");

		// Push function name to the stack
		lua_getglobal(l, "subtract_and_hello");
		// Push two numbers to the stack
		lua_pushinteger(l, 1);
		lua_pushinteger(l, 3);

		// Call the function
		const int num_args = 2;
		const int num_return_values = 2;
		lua_call(l, num_args, num_return_values);

		// Note that the stack is 1-indexed from the bottom
		const int diff = lua_tointeger(l, 1);
		const std::string greeting = lua_tostring(l, 2);

		// Pop the returned values from the stack
		lua_pop(l, 2);

		// Check that things worked correctly
		assert(diff == -2 && greeting == "hello");

		// Clean up the lua context

		lua_close(l);

	options opt;

	opt.add_option(std::wstring(L"-a"));
	opt.add_option(std::wstring(L"-b"));
	opt.add_option(std::wstring(L"-c"));
	opt.add_option(std::wstring(L"-d"));
	opt.add_option(std::wstring(L"-e"));

	if (build_options(std::wstring(L" -a=aOption -a=aOptionSecond -d -e -b=bOption "), opt) == false)
	{
		wprintf(L"error.\n");
		return 0;
	}

	std::vector< std::wstring > m;
	opt.values(std::wstring(L"-a"), m);
	assert(m[0] == std::wstring(L"aOption"));
	assert(m[1] == std::wstring(L"aOptionSecond"));

	assert(opt.first_value(std::wstring(L"-b")) == std::wstring(L"bOption"));

	assert(opt.is_supplied(L"-a"));
	assert(opt.is_supplied(L"-d"));
	assert(!opt.is_supplied(L"-k"));
	assert(!opt.is_supplied(L"-f"));
	return 0;
}

