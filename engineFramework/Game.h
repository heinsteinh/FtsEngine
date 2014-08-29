#pragma once

#include "Application.h"


namespace framework
{
	// *******************************************************************
	class Game
	{
		friend class Application;


	protected:
		// Abstract Class CTor
		Game();
		virtual ~Game();



		virtual bool OnInit();                                                  // Called just after game is first initialized.
		virtual void OnShutdown();                                              // Called just before the game is about to shut down.
		virtual void OnUpdate(float elapsedSeconds);
		virtual void OnDraw(float elapsedSeconds);

		// Singleton Access
		static Game* GetSingleton();

	private:
		// --------------------------------------
		// Internal Methods
		// --------------------------------------

		static Game* Singleton;
		static void CreateSingleton();

	};

	// The derived Game class MUST use this macro EXACTLY ONCE in the class .cpp file
#define FKH_GAME_CLASS(className) \
	void framework::Game::CreateSingleton() \
	{ \
	framework::Game::Singleton = new className(); \
	}

}

