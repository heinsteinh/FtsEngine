#pragma once


//https://github.com/jordanlaforest/2d-game-engine/blob/35bede9d300ed2a84467f052f829afeb90583a29/systems/RenderSystem.h

#include "System.h"
#include "ShaderProgram.h"
#include "SpriteBatch.h"

namespace rendering
{
	class RenderSystem: public core::System
	{
	public:
		RenderSystem();
		~RenderSystem();


		virtual bool init();
		virtual void update();
		virtual void shutdown();


		void preUpdate();
		void postUpdate();


	private:
		ShaderProgram shaderProgram;
		SpriteBatch* spriteBatch;
		GLuint vbo;
		GLuint vao;
		glm::mat4 vpMatrix;
	};

}

