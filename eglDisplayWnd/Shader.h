
#pragma  once 


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdio.h>
#include <memory>

#include "Engine.h"
#include "Uniform.h"
#include "Mesh.h"


namespace ANAS {


	//https://github.com/marcinlos/zephyr/blob/4afba790ae3b4d3bb6513c2c0d550b5df40f204a/Zephyr/src/zephyr/gfx/uniforms.hpp

	class ShaderBase {

	private:
		int shProgram;
		int shVertex;
		int shFragment;

		char *vString;
		char *fString;

		

		int LoadShader(int ShaderType, const char *Source){

			int newShader = glCreateShader(ShaderType);
			if (newShader){

				glShaderSource(newShader, 1, &Source, NULL);
				glCompileShader(newShader);

				GLint compiled = 0;
				glGetShaderiv(newShader, GL_COMPILE_STATUS, &compiled);
				if (!compiled)
				{
					LOGE("Shader: Compile Failed\n");
					GLint infoLen = 0;

					glGetShaderiv(newShader, GL_INFO_LOG_LENGTH, &infoLen);

					if (infoLen > 1)
					{
						char* infoLog = (char*)malloc(sizeof(char)* infoLen);

						glGetShaderInfoLog(newShader, infoLen, NULL, infoLog);
						LOGE("Error compiling shader:\n%s\n", infoLog);

						free(infoLog);
					}

					glDeleteShader(newShader);
					return 0;
				}

			}

			return newShader;

		}
	protected:

		virtual void onInit() = 0;
		virtual void onSet() = 0;

	public:

		

		ShaderBase(const char *vs, const char *fs) : shProgram(0), shVertex(0), shFragment(0){
			vString = (char*)vs;// new char[strlen(vs)];
			fString = (char*)fs;// new char[strlen(fs)];


		}
		

		virtual ~ShaderBase(){

	
			glUseProgram(NULL);

			glDetachShader(shProgram, shVertex);
			glDetachShader(shProgram, shFragment);

			glDeleteShader(shVertex);
			glDeleteShader(shFragment);

			glDeleteProgram(shProgram);

		}

		
		void Init(){

			// Load Shader
			shVertex = LoadShader(GL_VERTEX_SHADER, vString);
			shFragment = LoadShader(GL_FRAGMENT_SHADER, fString);


			// Create Program
			shProgram = glCreateProgram();

			if (shProgram){
				// Link Program
				glAttachShader(shProgram, shVertex);
				glAttachShader(shProgram, shFragment);

				glLinkProgram(shProgram);

				GLint linkStatus = GL_FALSE;
				glGetProgramiv(shProgram, GL_LINK_STATUS, &linkStatus);

				if (linkStatus != GL_TRUE){
					LOGE("Shader: Link Failed");
				}
			}
			else
			{
				LOGE("Shader: Can't create program");
			}


			onInit();

		}

		
		void Term(){

			glDetachShader(shProgram, shVertex);
			glDetachShader(shProgram, shFragment);
			glDeleteProgram(shProgram);
			glDeleteShader(shVertex);
			glDeleteShader(shFragment);

		}

		
		void Set(){
			glUseProgram(shProgram);

			onSet();
		}

		
		inline int GetProgram(){
			return shProgram;
		}


	};

};
