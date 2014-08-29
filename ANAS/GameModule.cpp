#include "stdafx.h"

#include "BridgeParameter.h"
#include "GameModule.h"


namespace win
{
	GameModule::GameModule(HINSTANCE &instance) :thewindow(instance), window(thewindow.window)
	{
		SetWindowLongPtr(window, GWLP_USERDATA, (LONG)&theinput);
		mInput = new ANAS::Input();
	}


	void GameModule::Shutdown(void)
	{			

		mInput->Term();

		delete mInput;
		mInput = NULL;
	}


	void GameModule::Show(bool show) 
	{
		if (show == true)
		{
			ShowWindow(this->window, SW_SHOW);
		}
		else {
			ShowWindow(this->window, SW_HIDE);
		}
	}



	bool GameModule::MainLoop(MSG* msg)
	{

		mInput->Init(msg);

		
		while (true)
		{
			while (PeekMessage(msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(msg);
				DispatchMessage(msg);
			}

			if (msg->message == WM_QUIT) {
				break;
			}
		}

		Sleep(30);

		
		return 0;
	}
}