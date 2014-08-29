#include "stdafx.h"
#include "RenderSystem.h"


//https://github.com/jordanlaforest/2d-game-engine/blob/35bede9d300ed2a84467f052f829afeb90583a29/systems/RenderSystem.h


namespace rendering
{
	RenderSystem::RenderSystem() :core::System("RenderSystem")
	{
		enableUpdater();
	}


	RenderSystem::~RenderSystem()
	{
	}


	bool RenderSystem::init()
	{
		System::init();
		
		spriteBatch = new  SpriteBatch(32 * 100);
	

		//Matrix setup
		vpMatrix = glm::ortho<float>(0.0f, 320, 480, 0.0f);
		glm::vec3 eye = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		vpMatrix *= glm::lookAt(eye, center, up);

		spriteBatch->setvpMatrix(vpMatrix);


		return true;
	}

	void RenderSystem::update()
	{

		System::update();
		
		preUpdate();





		postUpdate();
		GL_CHECK
	}


	void RenderSystem::shutdown()
	{
		System::shutdown();
		

		delete spriteBatch;

	}



	void RenderSystem::preUpdate()
	{
		//spriteBatch->begin(shaderProgram.getProgram());
	}

	void RenderSystem::postUpdate()
	{
		//spriteBatch->end();
	}

}