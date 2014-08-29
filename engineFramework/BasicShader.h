#pragma once


#include "Lib.h"
#include "shader_gl.h"


namespace core
{





	class BasicShader
	{

	private:
		unsigned int          mShader;

		//GL stuff
		SShader vertexShader;
		SShader fragmentShader;
		SShaderProgram program;

	public:
		BasicShader();
		~BasicShader();

		void Use();
		void Unuse();
		void LoadShaders( );
		int LocateUniform(const std::string& name);

		unsigned int my_uniforms[NUM_UNIFORMS];
	};


}