#pragma once

#include "Lib.h"
#include "shader_gl.h"
#include "BasicShader.h"

namespace core
{


	struct GLXVertex {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texUV;
	};


	class GLXShape {

	public:
		static void SetAttributePosition(GLuint index);
		static void SetAttributeNormal(GLuint index);
		static void SetAttributeTextureUV(GLuint index);

	private:
		std::vector<GLXVertex> mVertexData;
		int mVertexCount;

		GLuint mVertexArray;
		GLuint mVertexBuffer;


	protected:
		GLXShape();

	public:
		virtual ~GLXShape();

	public:
		void draw();

		BasicShader*				mProgram;

	protected:
		void addPolygon(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec2& uv1, const glm::vec2& uv2, const glm::vec2& uv3);
		void makeVBO();

		
	};


	class GLXShapePlane : public GLXShape {

	public:
		GLXShapePlane();

	};


	class GLXShapeCube : public GLXShape {

	public:
		GLXShapeCube(float size);

	};


	class GLXShapeCylinder : public GLXShape {

	public:
		GLXShapeCylinder(int divCount, float radius, float height);

	};


	class GLXShapeCone : public GLXShape {

	public:
		GLXShapeCone(int divCount, float radius, float height);

	};

	class GLXShapeSphere : public GLXShape {

	public:
		GLXShapeSphere(int divX, int divY, float radius);

	};

	class GLXShapeTorus : public GLXShape {

	public:
		GLXShapeTorus(int divCount, float radius1, float radius2);

	};

	class GLXShapeKlein : public GLXShape {

	public:
		GLXShapeKlein(int divCount, float radius1, float radius2);

	};

	class GLXShapeDrop : public GLXShape {

	public:
		GLXShapeDrop(int divCount, float radius, float height);

	};
}