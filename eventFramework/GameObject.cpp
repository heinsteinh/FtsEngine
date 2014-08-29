#include "stdafx.h"
#include "GameObject.h"

#include "XFormBuffer.h"

namespace BubbleBattleBoids
{
	//extern RenderThread* g_RenderThread;

	GameObject* GameObject::s_Head = NULL;
	GameObject* GameObject::s_Tail = NULL;

	GameObject::GameObject(const Vec2& position) : m_Damping(0.1f), m_Mass(1.f), m_Next(NULL), m_Prev(NULL), m_Shape(Circle), m_Dead(false)
	{
		// TODO: Not all objects need this data sync'd since it will never really change on static objects like walls or pits,
		// this could be a nice, simple optimization
		//GETSINGLE(g_XFormBuffer)->Add(this);
		XFormBufferManager::GetInstance().Add(this);


		SetPosition(position);
		SetScale(1.0f);

		if (s_Head == NULL)
		{
			s_Head = s_Tail = this;
		}
		else
		{
			s_Tail->m_Next = this;
			m_Prev = s_Tail;
			s_Tail = this;
		}
	}


	void GameObject::Unlink()
	{
		if (m_Next != NULL)
			m_Next->m_Prev = m_Prev;

		if (m_Prev != NULL)
			m_Prev->m_Next = m_Next;

		if (s_Head == this)
			s_Head = m_Next;
		if (s_Tail == this)
			s_Tail = m_Prev;
	}

	const Vec2& GameObject::GetPosition() const {
		return XFormBufferManager::GetInstance().Get(m_XFormId)->pos;
	}

	void GameObject::SetPosition(const Vec2& position)
	{
		XFormObject* obj = XFormBufferManager::GetInstance().Get(m_XFormId);
		obj->pos = m_PositionPrev = position;
	}


	float GameObject::GetScale() const { return XFormBufferManager::GetInstance().Get(m_XFormId)->scale; }
	void GameObject::SetScale(float scale)
	{
		XFormObject* obj = XFormBufferManager::GetInstance().Get(m_XFormId);
		obj->scale = scale;
	}



	void GameObject::IntegratePhysics()
	{
		XFormObject* obj = XFormBufferManager::GetInstance().Get(m_XFormId);

		float g_FrameTime = 1 / 60.0f;

		// integrate physics
		Vec2 accel = m_Force / m_Mass;
		Vec2 damping = -m_Damping * m_Velocity;
		m_Velocity = m_Velocity + (accel + damping) * g_FrameTime;
		m_Velocity = m_Velocity.Clamp(20.f);
		m_PositionPrev = obj->pos;
		obj->pos = obj->pos + m_Velocity * g_FrameTime;

		// clear force
		m_Force = Vec2();
	}


	void GameObject::CleanUp()
	{
		GameObject* obj = s_Head;
		while (obj != NULL)
		{
			if (obj->m_Dead)
			{
				GameObject* next = obj->m_Next;
				obj->Unlink();

				XFormBufferManager::GetInstance().Remove(obj->m_XFormId);

				// Can't safely delete shared memory from here! Must do it from render thread
				//XFormBufferManager::GetInstance().Send(new KillObjectMsg(obj));

				obj = next;
			}
			else
				obj = obj->m_Next;
		}
	}
}
