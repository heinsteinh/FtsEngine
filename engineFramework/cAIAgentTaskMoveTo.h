#pragma once


#include "Entity.h"
#include "StateMachine.h"




namespace sge
{

	//https://github.com/dpalma/sge/blob/98357c91eb77d6effe50dd11e926fb637f68a295/api/ai/aiagentapi.h
	bool AIAgentTaskMoveToCreate(const float point[3], entityx::Entity** ppTask);
	
	///////////////////////////////////////////////////////////////////////////////
	//
	// CLASS: cAIAgentTaskMoveTo
	//
	
	////////////////////////////////////////////////////////////////////////////////
	//
	// ENUM: eAIResult
	//

	//enum eAIResult
	//{
	//	E_AI_ERROR = E_FAIL,
	//	S_AI_CONTINUE = S_OK,
	//	S_AI_DONE = S_FALSE,
	//};

	typedef std::pair<entityx::Entity *, double> tAgentDoublePair;

	class cAIAgentTaskMoveTo : public entityx::Entity, public core::cStateMachine<cAIAgentTaskMoveTo, const tAgentDoublePair &>
	{
	public:

		cAIAgentTaskMoveTo(const float point[3]);
		~cAIAgentTaskMoveTo();

		virtual void Update(entityx::Entity* pAgent, double time);


	private:
		bool OnEnterMoving();
		bool OnExitMoving();
		void OnUpdateMoving(const tAgentDoublePair &);

		bool OnEnterArrived();
		bool OnExitArrived();
		void OnUpdateArrived(const tAgentDoublePair &);

		tState m_movingState;
		tState m_arrivedState;

		glm::vec3 m_moveGoal;
		float m_lastDistSqr;

		bool m_bJustStarted;
	};


}

