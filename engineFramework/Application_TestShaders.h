#pragma once

//https://github.com/welford/opengles_examples/blob/eaeb1b64cc71e0fd3c9faafd1c38742f93853c50/005/005.c

//https://code.google.com/p/overdriveassault/source/browse/trunk/Overdrive/app/test_shaders.cpp

#include "Application.h"
#include "WindowEGL.h"
#include "Input.h"

#include "wrapper_gl.h"
#include "shader_gl.h"
#include "XShape.h"

#include "CameraController.h"





#include "GraphicModule/Star.h"
#include "GraphicModule//Renderer.h"


namespace app
{
	/*
	* Tests various shaders
	*/
	class TestShaders :public Application
	{
	public:
		TestShaders();
		virtual ~TestShaders();

		virtual bool init();
		virtual void update();
		virtual void shutdown();

		void handle(const video::VideoSystem::WindowCreated& wc);
		void handle(const video::VideoSystem::RemoveWindow& wc);
		void handle(const input::Keyboard::KeyPressed& kp);
		void handle(const input::Keyboard::KeyReleased& kp);


		void pass1();
		void pass2();

	private:
	

		glm::mat4 mModel;
		glm::mat4 mView;
		glm::mat4 mProjection;

		float mAngle;

		core::GLXShapeSphere* mShape1;
		core::GLXShapeSphere* mShape2;		
	

		core::opengl::CameraController mCamera, mSecondCamera;
		float mCameraFar, mCameraNear, mOpeningAngle, mAspect;
		float mPhi, mTheta;
		glm::vec3 mCameraPosition, mCameraLookAt;
		glm::mat4 mLastView, mCurProjection;


		//GL stuff
		SShader vertexShader;
		SShader fragmentShader;
		SShaderProgram program;
		
	/*	zephyr::gfx::ShaderManager mShaderMgr;
		zephyr::gfx::ProgramManager mProgramMgr;*/
	

		zephyr::resources::Config* config;
		zephyr::resources::ResourceSystem mRSystem;
		zephyr::gfx::Renderer mRender;

#define WIDTH 16
#define HEIGHT 16
#define MAX_TEXTURES 5

		int ab = 0, eab = 0, w = 0, h = 0, uTex = 0;
		unsigned int position_attrib_idx = 0;
		unsigned int colour_attrib_idx = 1;
		unsigned int texture_attrib_idx = 2;
		int utex = 0, active_texture = 0;
		unsigned char * pTexture = 0;

		
		STextureObject tex[MAX_TEXTURES];

		core::EventChannel mChan;
		video::VideoSystem::eCamMode mCamMode;
	};
}



