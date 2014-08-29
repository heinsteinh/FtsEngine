#include "stdafx.h"
#include "cAIAgentTaskMoveTo.h"


namespace sge
{


	///////////////////////////////////////////////////////////////////////////////
	//
	// CLASS: cAIAgentTaskMoveTo
	//

	////////////////////////////////////////

	cAIAgentTaskMoveTo::cAIAgentTaskMoveTo(const float point[3]) : tStateMachine(&m_movingState)
		, m_movingState(&cAIAgentTaskMoveTo::OnEnterMoving, &cAIAgentTaskMoveTo::OnExitMoving, &cAIAgentTaskMoveTo::OnUpdateMoving)
		, m_arrivedState(&cAIAgentTaskMoveTo::OnEnterArrived
		, &cAIAgentTaskMoveTo::OnExitArrived
		, &cAIAgentTaskMoveTo::OnUpdateArrived)
		, m_moveGoal((point != NULL) ? glm::vec3(point[0], point[1], point[2]) : glm::vec3(0, 0, 0))
		, m_lastDistSqr(999999)
		, m_bJustStarted(true)
	{

	}

	////////////////////////////////////////

	cAIAgentTaskMoveTo::~cAIAgentTaskMoveTo()
	{
	}

	////////////////////////////////////////

	void cAIAgentTaskMoveTo::Update(entityx::Entity* pAgent, double time)
	{
		tStateMachine::Update(std::make_pair(pAgent, time));

		if (IsCurrentState(&m_arrivedState))
		{
			

		}

		
	}

	////////////////////////////////////////

	bool cAIAgentTaskMoveTo::OnEnterMoving()
	{
		return true;
	}

	////////////////////////////////////////

	bool cAIAgentTaskMoveTo::OnExitMoving()
	{
		return true;
	}

	////////////////////////////////////////

	void cAIAgentTaskMoveTo::OnUpdateMoving(const tAgentDoublePair & adp)
	{
	}

	////////////////////////////////////////

	bool cAIAgentTaskMoveTo::OnEnterArrived()
	{
		return true;
	}

	////////////////////////////////////////

	bool cAIAgentTaskMoveTo::OnExitArrived()
	{
		return true;
	}

	////////////////////////////////////////

	void cAIAgentTaskMoveTo::OnUpdateArrived(const tAgentDoublePair &)
	{
	}

	////////////////////////////////////////
//
//	bool AIAgentTaskMoveToCreate(const float point[3], entityx::Entity** ppTask)
//	{
//		//https://github.com/dpalma/sge/blob/98357c91eb77d6effe50dd11e926fb637f68a295/ai/aiagenttaskmoveto.cpp
//
//		typedef std::shared_ptr<entityx::Entity> Ptr;
//		if (point == NULL || ppTask == NULL)
//		{
//			return false;
//		}
//		entityx::EntityManager em;
//		entityx::Entity pEntity= em.create();
//
//		std::shared_ptr<entityx::Entity> pTask(static_cast<entityx::Entity*>(new cAIAgentTaskMoveTo(point)));
//		*ppTask = pTask.get();
//		
//		return true;
//	}

}