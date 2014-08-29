#pragma once

#include "StateMachine.h"

//https://github.com/jswigart/omnibot/blob/96b7db730ffed31edc51e0cfbd8e14aa659b50d7/Omnibot/Common/BotSteeringSystem.h

class SteeringSystem : public core::cStateMachine<SteeringSystem, double>
{
public:
	SteeringSystem();
	~SteeringSystem();
};

