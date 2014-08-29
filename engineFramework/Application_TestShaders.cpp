#include "stdafx.h"
#include "Application_TestShaders.h"
#include "VideoSystem.h"
#include "WindowEGL.h"
#include "Engine.h"



#include "GraphicModule/Mesh.h"
#include "GraphicModule/ResourceManager.h"
#include "GraphicModule/Star.h"
#include "GraphicModule/Renderer.h"
#include "GraphicModule/Objects.h"



namespace app
{

	
	static const float vertices[] = {
		//0
		-0.5f, -0.5f, 0.0f, ///VVV
		1.0f, 1.0f, 1.0f, ///CCC
		-0.5f, -0.5f,	///TX
		//1
		0.5f, -0.5f, 0.0f, ///VVV
		0.0f, 0.0f, 1.0f, ///CCC
		1.5f, -0.5f,	///TX
		//2
		+0.5f, 0.5f, 0.0f, ///VVV
		0.0f, 0.0f, 1.0f, ///CCC
		1.5f, 1.5f,	///TX
		//3
		-0.5f, 0.5f, 0.0f, ///VVV
		1.0f, 0.0f, 0.0f, ///CCC
		-0.5f, 1.5f	///TX
	};

	static unsigned char indices[] = { 0, 1, 3, 2 };

#define STRINGIFY(A)  #A

	const GLchar* pVertex = STRINGIFY(
		attribute vec4 position;
		attribute vec3 colour; 
		attribute vec2 texture; 
		varying vec3 vColour; 
		varying vec2 vTexture; 
		void main() {
				gl_Position = vec4(position.xyz, position.w); 
				vColour = colour; 
				vTexture = texture; 
		}
	);

	const GLchar* pFragment = STRINGIFY(
		precision highp float;
	varying vec3 vColour;
	varying vec2 vTexture;
	uniform sampler2D tex;
	void main() {
		gl_FragColor = texture2D(tex, vTexture.st);
	}
	);

	static const char* pVertexShader = "\
									   attribute vec4 position;\n\
									   attribute vec3 colour;\n\
									   attribute vec2 texture;\n\
									   varying vec3 vColour;\n\
									   varying vec2 vTexture;\n\
									   void main() {\n\
									   gl_Position = vec4(position.xyz,position.w);\n\
									   vColour = colour;\n\
									   vTexture = texture;\n\
									   }\n";


	static const char* pFragmentShader = "\
										  precision highp float; \
										 varying vec3 vColour;\n\
										 varying vec2 vTexture;\n\
										 uniform sampler2D tex;\
										 void main() {\n\
										 //gl_FragColor = vec4(vColour,1.0);\n\
										 gl_FragColor = texture2D(tex, vTexture.st);\n\
										 }\n";

	




	TestShaders::TestShaders()
		: Application("TEST: Shaders", core::Task::SINGLETHREADED_REPEATING), mRSystem(*config), mRender(mRSystem)
	{		
		mChan.add<input::Keyboard::KeyPressed>(*this);
		mChan.add<input::Keyboard::KeyReleased>(*this);

		mChan.add<video::VideoSystem::WindowCreated>(*this);
		mChan.add<video::VideoSystem::RemoveWindow>(*this);

		config = NULL;
		 
	}


	TestShaders::~TestShaders() {
		mChan.remove<input::Keyboard::KeyPressed>(*this);
		mChan.remove<input::Keyboard::KeyReleased>(*this);
		mChan.remove<video::VideoSystem::WindowCreated>(*this);
		mChan.remove<video::VideoSystem::RemoveWindow>(*this);
	}

	bool TestShaders::init() 
	{
		System::init();
		mEngine->getVideo()->setCameraMode(video::VideoSystem::PERSPECTIVE);
		
		core::GLXShape::SetAttributePosition(ATTRIB_VERTEX);
		core::GLXShape::SetAttributeNormal(ATTRIB_NORMAL);
		core::GLXShape::SetAttributeTextureUV(ATTRIB_TEXTURE_UV);

		mShape1 = new core::GLXShapeSphere(20, 20, 0.05f);
		mShape2 = new core::GLXShapeSphere(100, 100, 5.0f);
		

		//zephyr::resources::Config* config = NULL;
		//zephyr::resources::ResourceSystem mRSystem(*config);
		//zephyr::gfx::Renderer mRender(mRSystem);

		zephyr::gfx::ShaderManager mShaderMgr;
		zephyr::gfx::ProgramManager mProgramMgr;
		zephyr::gfx::MeshPtr myStar;


		std::string name = "BasicShader";
		myStar = zephyr::gfx::makeStar(3, 6);

		zephyr::gfx::ShaderBuilder sb_vert(GL_VERTEX_SHADER);
		zephyr::gfx::ShaderBuilder sb_frag(GL_FRAGMENT_SHADER);


		sb_vert.append(pVertexShader);
		sb_frag.append(pFragmentShader);

		zephyr::gfx::ShaderPtr vershader = sb_vert.create();
		zephyr::gfx::ShaderPtr fragshader = sb_frag.create();

		std::vector<zephyr::gfx::ShaderPtr> shaders_vec;
		shaders_vec.push_back(vershader);
		shaders_vec.push_back(fragshader);


		mShaderMgr.put(name, vershader);
		mShaderMgr.put(name, fragshader);


		zephyr::gfx::ProgramPtr prog = zephyr::gfx::newProgram(shaders_vec);
		mProgramMgr.put(name, prog);


		zephyr::gfx::MeshPtr m_mesh = zephyr::gfx::makeStar(3, 6);
		zephyr::gfx::ProgramPtr m_program = mProgramMgr.get(name);

		zephyr::gfx::MaterialPtr  m_material = zephyr::gfx::newMaterial(m_program);
		glm::mat4 mtransform = glm::mat4(1.0f);

		zephyr::gfx::EntityPtr entity = zephyr::gfx::newEntity(m_material, m_mesh);
		zephyr::gfx::Renderable to_render{ entity, mtransform };


		
		//mRSystem.programs.put(name, m_program);
		//mRSystem.meshes.put("Star", myStar);
		//mRSystem.entities.put("Entity", entity);
		//mRSystem.materials.put("Material1", m_material);


		mRender.submit(to_render);
		

		
		

		GL_CHECK
			
		
			STextureDescriptor desc = { TEX_2D, TEX_FMT_RGB, WIDTH, HEIGHT, 0, 0, GEN_MIPMAP };
		STextureParam param[] = {
			//tex 0
			{ MIN_FILTER, PARAM_NEAREST },
			{ MAG_FILTER, PARAM_NEAREST },
			{ WRAP_S, PARAM_REPEAT },
			{ WRAP_T, PARAM_REPEAT },
			// tex 1
			{ MIN_FILTER, PARAM_LINEAR },
			{ MAG_FILTER, PARAM_LINEAR },
			{ WRAP_S, PARAM_REPEAT },
			{ WRAP_T, PARAM_REPEAT },
			// tex 2
			{ MIN_FILTER, PARAM_LINEAR },
			{ MAG_FILTER, PARAM_LINEAR },
			{ WRAP_S, PARAM_REPEAT },
			{ WRAP_T, PARAM_CLAMP_TO_EDGE },
			// tex 3
			{ MIN_FILTER, PARAM_LINEAR },
			{ MAG_FILTER, PARAM_LINEAR },
			{ WRAP_S, PARAM_CLAMP_TO_EDGE },
			{ WRAP_T, PARAM_CLAMP_TO_EDGE },
			// tex 4
			{ MIN_FILTER, PARAM_NEAREST },
			{ MAG_FILTER, PARAM_NEAREST },
			{ WRAP_S, PARAM_CLAMP_TO_EDGE },
			{ WRAP_T, PARAM_CLAMP_TO_EDGE },
		};
		SPixelData pixelData = { PX_RGB, PX_UNSIGNED_BYTE, 0, 0 };

		//GL stuff
		SShader vertexShader;
		SShader fragmentShader;
		SShaderProgram program;

		
		pTexture = (unsigned char*)malloc(WIDTH * HEIGHT * 3);
		for (h = 0; h<HEIGHT; h++)
		for (w = 0; w<WIDTH; w++)
		{
			pTexture[(h*WIDTH * 3) + (w * 3) + 0] = (255 * w) / (WIDTH);	//R
			pTexture[(h*WIDTH * 3) + (w * 3) + 1] = (255 * h) / (HEIGHT);	//G
			pTexture[(h*WIDTH * 3) + (w * 3) + 2] = (255 * (w + h)) / (WIDTH + HEIGHT);	//B
		}
		pixelData.pData = (void*)pTexture;

		ActiveTexture(UNIT_0);
		GL_CHECK
		//tex 0
		if (CreateBaseTexture(&tex[0], &desc))
		{
			GL_CHECK
			UpdateTextureData(&tex[0], &pixelData);
			GL_CHECK
			SetTextureParams(&tex[0], param, 4);
			GL_CHECK
		}
		GL_CHECK
		//tex 1
		if (CreateBaseTextureData(&tex[1], &desc, &pixelData))
			SetTextureParams(&tex[1], param + 4, 4);
		GL_CHECK
		//tex 2
		if (CreateBaseTextureData(&tex[2], &desc, &pixelData))
			SetTextureParams(&tex[2], param + 8, 4);
		//tex 3
		if (CreateBaseTextureData(&tex[3], &desc, &pixelData))
			SetTextureParams(&tex[3], param + 12, 4);
		//tex 4
		if (CreateBaseTextureData(&tex[4], &desc, &pixelData))
			SetTextureParams(&tex[4], param + 16, 4);
		free(pTexture);

		//-------------------
		//setup the shaders
		//CreateShader(&vertexShader, VERT, &pVertexShader, 1);
		//CreateShader(&fragmentShader, FRAG, &pFragmentShader, 1);
		CreateShader(&vertexShader, VERT, &pVertex, 1);
		CreateShader(&fragmentShader, FRAG, &pFragment, 1);
		GL_CHECK
		CreateShaderProgram(&program);
		AddShaderToProgram(&program, &vertexShader);
		AddShaderToProgram(&program, &fragmentShader);
		SetAttributeLocation(&program, position_attrib_idx, "position");
		SetAttributeLocation(&program, colour_attrib_idx, "colour");
		SetAttributeLocation(&program, texture_attrib_idx, "texture");
		LinkShaderProgram(&program);
		uTex = GetUniformLocation(&program, "tex");
		
		GL_CHECK

		ab = CreateBufferUsingData(BUFFER_ARRAY, BUFFER_STATIC, sizeof(vertices), vertices);
		eab = CreateBufferUsingData(BUFFER_ELEMENTS, BUFFER_STATIC, sizeof(indices), indices);

		//-------------------
		//tell openGL how to interperet the data
		BindBuffer(BUFFER_ELEMENTS, eab);
		BindBuffer(BUFFER_ARRAY, ab);
		SVertexAttribute attr[] = {
			{ ab, position_attrib_idx, 3, STREAM_FLOAT, 0, 32, 0, 0 },//P
			{ ab, colour_attrib_idx, 3, STREAM_FLOAT, 0, 32, 12, 0 },	//C
			{ ab, texture_attrib_idx, 2, STREAM_FLOAT, 0, 32, 24, 0 }	//T
		};
		SetAttributeFormat(attr, 3, 0);
		//set rendering states
		EnableCulling(1);
		SetClearColour(0, 0, 0, 0.0f); //alpha to 0, should make triangle appear over console

		Start(&program);
		SetTextureUnitByLocation(utex, 0);
		BindTexture(tex + active_texture);
		printf("Texture Index %d, id %d\n", active_texture, tex[active_texture]);

		GL_CHECK

		return true;
	}

	
	
	void TestShaders::update()
	{


		//mRender.render();
		
		mCamera.updateCamera();
		//mSecondCamera.updateCamera();

		glm::mat4 view = mCamera.getModelViewMat();
		glm::mat4 projection = glm::ortho(-0.5f*mCamera.getAspect(), 0.5f*mCamera.getAspect(), 0.5f, -0.5f, 0.1f, 1000.0f);


		switch (mCamMode) {
		case video::VideoSystem::PERSPECTIVE:
			projection = mCamera.getProjectionMat();
			break;
		case video::VideoSystem::ORTHOGRAPHIC:
			break;
		case video::VideoSystem::LEFT:
			view = glm::lookAt(glm::vec3(-1, 0, 0), glm::vec3(0.0), glm::vec3(0, 1, 0));
			break;
		case video::VideoSystem::RIGHT:
			view = glm::lookAt(glm::vec3(1, 0, 0), glm::vec3(0.0), glm::vec3(0, 1, 0));
			break;
		case video::VideoSystem::TOP:
			view = glm::lookAt(glm::vec3(0, 1, 0), glm::vec3(0.0), glm::vec3(0, 0, 1));
			break;
		case video::VideoSystem::BOTTOM:
			view = glm::lookAt(glm::vec3(0, -1, 0), glm::vec3(0.0), glm::vec3(0, 0, 1));
			break;
		}


		mLastView = view;
		mCurProjection = projection;

		pass1();
		//pass2();

		//

		mAngle += 0.001f;
	}


	void TestShaders::pass1()
	{
		
		 

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear old data
		glEnable(GL_DEPTH_TEST); //enable depth testing


		mShape1->mProgram->Use();



		glm::mat4 Model     = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 Modelview = mLastView*glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 ModelViewProj  = mCurProjection * Modelview;


		glUniformMatrix4fv(mShape1->mProgram->my_uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, 0, &ModelViewProj[0][0]);
		glUniformMatrix4fv(mShape1->mProgram->my_uniforms[UNIFORM_MODEL_MATRIX], 1, 0, &Model[0][0]);
		
		glUniform3fv(mShape1->mProgram->my_uniforms[UNIFORM_LIGHT_VECTOR], 1, glm::value_ptr(glm::vec3(0.3, 0.1, 1)));
					

		mShape1->draw();
				

		mShape1->mProgram->Unuse();
	}

	void TestShaders::pass2()
	{

		{
			if (++active_texture >= MAX_TEXTURES)
				active_texture = 0;
			BindTexture(tex + active_texture);
			printf("Texture Index %d, id %d\n", active_texture, tex[active_texture]);
		}

		ClearScreenBuffer(COLOR_BIT);
		Draw(DRAW_TRIANGLE_STRIP, ELEMENT_BYTE, sizeof(indices) / sizeof(unsigned char), 0);

		
		GL_CHECK
	}


	void TestShaders::shutdown() 
	{
		System::shutdown();
	
		if (mShape1)
			delete mShape1;
		

		if (mShape2)
			delete mShape2;
		

		mShape1 = NULL;
		mShape2 = NULL;

		Stop();
		DeleteShaderProgram(&program);
		DeleteShader(&vertexShader);
		DeleteShader(&fragmentShader);
	}


	void TestShaders::handle(const video::VideoSystem::WindowCreated& wc)
	{
		auto width = wc.mWindow->GetWidth();
		auto height = wc.mWindow->GetHeight();

	
		//projection could remain constant		 
		float aspect = wc.mWindow->GetWindowAspectRatio();
		mProjection = glm::perspective(60.0f, aspect, 0.3f, 100.0f);

		//https://github.com/AlexanderKnueppel/Harmony4D/blob/6c2302c4f8092ffc3d6589c4b4834f2c01fa4211/Harmony4D/include/H4DApplication/ViewWidget.h

		mCamera = core::opengl::CameraController(3.1415f*0.25f, 3.1415f*0.25f, 5.f);
		mCamera.setFar(150.0f);
		mCamera.setNear(0.1f);
		mCamera.setAspect(aspect);
		mCamera.setOpeningAngle(45.0f);

		mSecondCamera = core::opengl::CameraController(0.f, 0.f, 1.5f);
		mSecondCamera.setFar(3.0f);
		mSecondCamera.setNear(0.2f);
		mSecondCamera.setAspect(1.34f);
		mSecondCamera.setOpeningAngle(45.0f);

		mCameraFar = 3.0f;
		mCameraNear = 0.2f;
		mOpeningAngle = 45.0f;
		mAspect = 1.34f;
		mCameraPosition = glm::vec3(0.f, 0.f, 1.5f);
		mCameraLookAt = glm::vec3(0.0f);
		mPhi = mTheta = 0;

		mCamMode = mEngine->getVideo()->getCameraMode();


		//set the viewport to the eniter window
		glViewport(0, 0, width, height);
	}

	void TestShaders::handle(const video::VideoSystem::RemoveWindow& wc)
	{

	}
	


	void TestShaders::handle(const input::Keyboard::KeyPressed& kp)
	{

		//core::EventChannel evt;
		float x = 0;
		float y = 0;

		switch (kp.mKey)
		{
		case WM_QUIT:
			mChan.broadcast(core::TaskManager::StopEvent());
			break;

		case VK_F1:
			mLog << "VK_F1";
			mCamera.move(core::opengl::CameraController::MOVE_FORWARD);		
			//evt.broadcast(input::Keyboard::KeyReleased(VK_F1));

			break;
		case VK_F2:
			mLog << "VK_DOWN";
			mCamera.move(core::opengl::CameraController::MOVE_BACKWARD);
			//evt.broadcast(input::Keyboard::KeyReleased(VK_F2));
			break;

		case VK_UP:
			mLog << "VK_UP";
			mCamera.move(core::opengl::CameraController::MOVE_UP);
			//evt.broadcast(input::Keyboard::KeyReleased(VK_UP));
			break;
		case VK_DOWN:
			mLog << "VK_DOWN";
			mCamera.move(core::opengl::CameraController::MOVE_DOWN);			
			//evt.broadcast(input::Keyboard::KeyReleased(VK_DOWN));
			break;
		case VK_LEFT:
			mLog << "VK_LEFT";
			mCamera.move(core::opengl::CameraController::MOVE_LEFT);
			//evt.broadcast(input::Keyboard::KeyReleased(VK_LEFT));

			break;
		case VK_RIGHT:
			mLog << "VK_RIGHT";
			mCamera.move(core::opengl::CameraController::MOVE_RIGHT);			
			//evt.broadcast(input::Keyboard::KeyReleased(VK_RIGHT));
			break;

			default:
				break;
		}
	}


	void TestShaders::handle(const input::Keyboard::KeyReleased& kp)
	{

		float x = 0;
		float y = 0;

		switch (kp.mKey)
		{
		case WM_QUIT:
			mChan.broadcast(core::TaskManager::StopEvent());
			break;

		case VK_F1:
			mLog << "VK_F1";
			mCamera.stop(core::opengl::CameraController::MOVE_FORWARD);
			break;

		case VK_F2:
			mLog << "VK_DOWN";
			mCamera.stop(core::opengl::CameraController::MOVE_BACKWARD);
			break;

		case VK_UP:
			mLog << "VK_UP";
			mCamera.stop(core::opengl::CameraController::MOVE_UP);
			break;
		case VK_DOWN:
			mLog << "VK_DOWN";
			mCamera.stop(core::opengl::CameraController::MOVE_DOWN);
			break;

		case VK_LEFT:
			mCamera.stop(core::opengl::CameraController::MOVE_LEFT);
			mLog << "VK_LEFT";
			break;
		case VK_RIGHT:
			mLog << "VK_RIGHT";
			mCamera.stop(core::opengl::CameraController::MOVE_RIGHT);
			break;
		}

	}
}