#pragma once

#include "Shader.h"
#include "Engine.h"
#include "Mesh.h"
#include "Texture.h"
#include "Resource.h"

const char mtVertShader[] = STRINGIFY(
	uniform mat4 u_mvpMatrix;
attribute vec4 a_position;
attribute vec2 a_texCoord;
varying vec2 v_texCoord;
void main()
{
	gl_Position = u_mvpMatrix*a_position;
	v_texCoord = a_texCoord;
}
);

const char mtFragShader[] = STRINGIFY(
	precision mediump float;
varying vec2 v_texCoord;
uniform sampler2D s_rock;
uniform sampler2D s_dirt;
uniform sampler2D s_grass;
uniform sampler2D s_blend;
void main()
{
	vec4 rockColor;
	vec4 dirtColor;
	vec4 grassColor;
	vec4 blendColor;

	rockColor = texture2D(s_rock, v_texCoord);
	dirtColor = texture2D(s_dirt, v_texCoord);
	grassColor = texture2D(s_grass, v_texCoord);
	blendColor = texture2D(s_blend, v_texCoord);

	gl_FragColor = (rockColor*blendColor.r + dirtColor*blendColor.g + grassColor*blendColor.b)*blendColor.a;
}
);





class MultiTextureShader : public ANAS::ShaderBase
{

private:

	ANAS::Uniform<int, 1> u_LocRockSampler_index;
	ANAS::Uniform<int, 1> u_LocDirtSampler_index;
	ANAS::Uniform<int, 1> u_LocGrassSampler_index;
	ANAS::Uniform<int, 1> u_LocBlendSampler_index;
	
	ANAS::Uniform<glm::mat4, 4>  u_modelViewProjectionMatrix_index;
	ANAS::Uniform<glm::mat4, 4>  u_normalMatrix_index;


	GLint iLocRockSampler, iLocDirtSampler, iLocGrassSampler, iLocBlendSampler;

	GLint iLocPosition = 0;
	GLint iLocColour, iLocTexCoord;
	
	GLint iLocMVP = -1;
	GLuint rockTexId, dirtTexId, grassTexId, blendTexId;
	
	CTexture* pTextureRock  = NULL;
	CTexture* pTextureDirt  = NULL;
	CTexture* pTextureGrass = NULL;
	CTexture* pTextureBlend = NULL;


	glm::mat4 matModel;
	glm::mat4 matModelView;
	glm::mat4 matModelViewProj;


protected:

	void onInit(){



		glGetError();


		u_LocRockSampler_index.Init(GetProgram(), "s_rock");
		u_LocDirtSampler_index.Init(GetProgram(), "s_dirt");
		u_LocGrassSampler_index.Init(GetProgram(), "s_grass");
		u_LocBlendSampler_index.Init(GetProgram(), "s_blend");

		u_modelViewProjectionMatrix_index.Init(GetProgram(), "u_mvpMatrix");

		
		// Get the attribute locations
		iLocPosition = glGetAttribLocation(GetProgram(), "a_position");
		iLocTexCoord = glGetAttribLocation(GetProgram(), "a_texCoord");


		int error;
		if ((error = glGetError()) != GL_NO_ERROR){
			LOGE("MultiTextureShader", "Init error");
			switch (error){
			case GL_INVALID_ENUM:
				LOGE("MultiTextureShader", "GL_INVALID_ENUM");
				break;
			case GL_INVALID_VALUE:
				LOGE("MultiTextureShader", "GL_INVALID_VALUE");
				break;
			case GL_INVALID_OPERATION:
				LOGE("MultiTextureShader", "GL_INVALID_OPERATION");
				break;
			case GL_OUT_OF_MEMORY:
				LOGE("MultiTextureShader", "GL_OUT_OF_MEMORY");
				break;
			}
		}
	}

	void onSet(){
		
		u_LocRockSampler_index.SetValue(dirtTexId);
		u_LocDirtSampler_index.SetValue(dirtTexId);
		u_LocGrassSampler_index.SetValue(dirtTexId);
		u_LocBlendSampler_index.SetValue(dirtTexId);
	}


public:

	MultiTextureShader() : ANAS::ShaderBase(mtVertShader, mtFragShader){	

		rockTexId, dirtTexId, grassTexId, blendTexId;
	}

	~MultiTextureShader(){
	}


	
};