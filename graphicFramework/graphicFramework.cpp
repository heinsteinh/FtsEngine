// graphicFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ResourceSystem.h"
#include "ResourceManager.h"
#include "Star.h"
#include "Renderer.h"
#include "Objects.h"


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
int _tmain(int argc, _TCHAR* argv[])
{

	zephyr::resources::Config* config =NULL;
	zephyr::resources::ResourceSystem mRSystem(*config);
	zephyr::gfx::ShaderManager mShaderMgr;
	zephyr::gfx::ProgramManager mProgramMgr;
	zephyr::gfx::MeshPtr myStart;
	zephyr::gfx::Renderer mRender(mRSystem);

	/*zephyr::gfx::ShaderPtr vs = mRSystem.shader("BasicShader");
	zephyr::gfx::ShaderPtr fs = mRSystem.shader("BasicShader");*/
	

	
	std::string name = "BasicShader";
	myStart = zephyr::gfx::makeStar(3, 6);

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


	mRSystem.shaders.put("VertShader", vershader);
	mRSystem.shaders.put("FragShader", fragshader);
	

	zephyr::gfx::ProgramPtr prog = zephyr::gfx::newProgram(shaders_vec);
	mProgramMgr.put(name, prog);

	mRSystem.programs.put("BasicProg", prog);



	zephyr::gfx::MeshPtr m_mesh = zephyr::gfx::makeStar(3, 6);
	zephyr::gfx::ProgramPtr m_program = mProgramMgr.get(name);

	zephyr::gfx::MaterialPtr  m_material = zephyr::gfx::newMaterial(m_program);
	glm::mat4 mtransform = glm::mat4(1.0f);

	zephyr::gfx::EntityPtr entity = zephyr::gfx::newEntity(m_material, m_mesh);
	zephyr::gfx::Renderable to_render{ entity, mtransform };

	mRender.submit(to_render);


	mRender.render();

	return 0;
}

