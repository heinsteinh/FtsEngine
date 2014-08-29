#pragma once

#include "Lib.h"

//https://github.com/jordanlaforest/2d-game-engine/blob/35bede9d300ed2a84467f052f829afeb90583a29/helper/rendering/SpriteBatch.h

namespace rendering
{

	//Number of floats per vertex
#define VERTEX_SIZE 8
	class Texture;
	class Sprite;
	class SpriteBatch
	{
	public:
		SpriteBatch(unsigned int size);
		~SpriteBatch();

		void begin(GLuint program);
		void draw(Sprite* s, glm::vec2 pos, glm::vec2 scale, glm::vec4 tint, float rotation);
		void end();

		void flush();

		void setvpMatrix(glm::mat4& newMatrix);

	private:
		void checkFlush(Texture*);
		void render();
		void addVertexData(glm::vec4& pos, glm::vec4& tint, glm::vec2& texCoords);
		void addQuadIndices();

		Texture* currentTexture;
		int renderCalls;
		GLfloat* vertexBuffer;
		unsigned int bufIndex;
		GLushort* indices;
		unsigned int indIndex;
		bool drawing;
		unsigned int maxIndex;
		glm::mat4 vpMatrix;

		GLint vpMatLocation;
		GLint textureLocation;
		GLint positionLocation;
		GLint texCoordLocation;

		GLuint vbo;
		GLuint vao;
	};

}