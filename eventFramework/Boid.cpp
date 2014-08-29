#include "stdafx.h"
#include "Boid.h"


namespace BubbleBattleBoids
{

	// Boid objects
	int Boid::s_Count = 0;

	Boid::Boid(const Vec2& position) : GameObject(position), m_MaxSpeed(1.f), m_MaxSteeringForce(1.f), m_Anger(0.f), m_WanderTheta(0.f)
	{
		SetScale(0.4f);
		++s_Count;
	}

	Boid::~Boid()
	{
		--s_Count;
	}

	struct NearestBoids
	{
		Boid* boid;
		float distance;
	};

	void Boid::InsertClosest(Boid* boid, float distance, BoidFriend* boids, int& count, int maxCount)
	{
		if (count < maxCount)
		{
			boids[count].boid = boid;
			boids[count].distance = distance;
			++count;
		}
		else
		{
			for (int i = 0; i != maxCount; ++i)
			{
				if (distance < boids[i].distance)
				{
					std::swap(boid, boids[i].boid);
					std::swap(distance, boids[i].distance);
					InsertClosest(boid, distance, boids, count, maxCount);
					break;
				}
			}
		}
	}



	void Boid::FindClosest(BoidFriend* boids, int& count, int maxCount)
	{
		count = 0;

		for (GameObject* obj = GameObject::All(); obj != NULL; obj = obj->GetNext())
		{
			if (obj != this)
			{
				Vec2 delta = GetPosition() - obj->GetPosition();
				float dist = delta.Length();

				// average position and direction for boids close enough to matter
				if (dist < 2.25f)
					InsertClosest((Boid*)obj, dist, boids, count, maxCount);
			}
		}
	}


	void Boid::PreUpdate(){}
	void Boid::PostUpdate(){}
	void Boid::Draw(XFormObject* obj){}
	void Boid::Collision(GameObject* other, const Vec2& point, const Vec2& normal){}


}
