#pragma once

#include "Lib.h"

namespace rendering
{

	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		//Gets a shader ready to be linked
		//The shader will be deleted after linking
		bool addShaderFromString(GLenum shaderType, const std::string& shaderString);
		bool addShaderFromFile(GLenum shaderType, const std::string& shaderFilename);
		//Links the shaders and creates the shader program object
		//which will be deleted when this class is
		bool linkShaders();

		//Returns the id of the program to be used with OpenGL
		//Returns zero if it is not ready yet (not linked, no shaders added)
		GLuint getProgram();

	private:
		GLuint program;
		std::list<GLuint> shaders;


	};
}