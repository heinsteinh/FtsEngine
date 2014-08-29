// messageFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MessageHelper.h"


#include "Functions.h"


int _tmain_(int argc, _TCHAR* argv[])
{

	Messenger messenger;

	messenger.subscribe(STRING, [](const StringMessage& msg)
	{
		std::cout << "Received (1): " << msg.message << std::endl;
	});

	std::function<void(const StringMessage& msg)> func = [](const StringMessage& msg)
	{
		std::cout << "Received (2): " << msg.message << std::endl;
	};
	messenger.subscribe(STRING, func);

	messenger.send(StringMessage("Hello, messages!"));
	

	return 0;
}

