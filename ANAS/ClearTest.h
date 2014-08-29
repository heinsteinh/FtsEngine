#pragma once

#include "EglDisplay.h"

namespace ANAS
{
	class ClearTest : public EglDisplay
	{
	
	public:

		ClearTest()
		{
			setWindowWidth(320);
			setWindowHeight(480);
			setConfigRedBits(8);
			setConfigGreenBits(8);
			setConfigBlueBits(8);
			setConfigAlphaBits(8);
			setConfigDepthBits(24);



			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glClearColor(0.0, 1.0, 0.0, 1.0);
			glClearDepthf(0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			

			GLuint fbo;
			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			GLuint rbo;
			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB565, 16, 16);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo);

		}



		virtual void Init()
		{
			EglDisplay::Init();

			const std::string vertexShaderSource = SHADER_SOURCE
				(
				precision highp float;
			attribute vec4 position;
			void main()
			{
				gl_Position = position;
			}
			);


			const std::string fragmentShaderSource = SHADER_SOURCE
				(
				precision highp float;

			void main()
			{
				gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
			}
			);


			mProgram = compileProgram(vertexShaderSource, fragmentShaderSource);
			if (mProgram == 0)
			{
				gLog << "shader compilation failed.";
			}
		}

		virtual void ShutDown()
		{
			glDeleteProgram(mProgram);
			EglDisplay::ShutDown();
		}


		GLuint mProgram;



		void Render()
		{

			glViewport(0, 0, getWindowWidth(), getWindowHeight());

			static float i = 0;			
			glClearColor((i), (i), 1.0f, 1.0f);			
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			
	
			//drawQuad(mProgram, "position", 0.5f);


			swapBuffers();			

			i++;
		}
	};
}