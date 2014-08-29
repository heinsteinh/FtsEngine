#pragma once

#include "Engine.h"
#include "IphoneGraphics.h"

#include <vector>


namespace gamelevel
{

	class IphoneCommand;
	class GameLevel
	{
	public:
		virtual void render(const glm::mat4 &world) = 0;
		virtual int        sendIphoneCommand(IphoneCommand* command,            // the command sent
			bool commandState,           // state true/false
			int commandValue,             // optional integer command value
			float commandFloatValue,          // optional float value
			void *commandData) {
			return true;
		}
		            // optional additional command data. Not const, because it might possible be used to return data values.
	};


	GameLevel * createGameLevel(const char *data);
	void        releaseGameLevel(GameLevel *g);



}