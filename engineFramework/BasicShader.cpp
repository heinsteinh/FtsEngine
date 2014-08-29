#include "stdafx.h"
#include "BasicShader.h"


namespace core
{


	

#define STRINGIFY(A)  #A

	const GLchar* pVertex = STRINGIFY(

		attribute vec4 position;
	attribute vec3 normal;
	attribute vec2 texUV;

	varying lowp vec3 colorVarying;
	varying lowp vec2 texUVVarying;

	uniform mat4 modelMatrix;
	uniform mat4 modelViewProjectionMatrix;
	uniform mat3 normalMatrix;
	uniform vec3 lightVec;

	void main()
	{
		vec3 diffuseColor = vec3(1.0, 1.0, 1.0);
		vec3 ambientColor = vec3(0.1, 0.1, 0.1);
		vec3 theNormal = mat3(modelMatrix) * normal;

		float nDotVP = max(0.0, dot(theNormal, normalize(-lightVec)));

		colorVarying = diffuseColor * nDotVP + ambientColor;

		gl_Position = modelViewProjectionMatrix * position;
		texUVVarying = texUV;
	}
	);


	const GLchar* pFragment = STRINGIFY(
		precision highp float;

	varying lowp vec3 colorVarying;
	varying lowp vec2 texUVVarying;

	uniform sampler2D texture0;

	void main()
	{
		lowp vec4 texColor0 = texture2D(texture0, texUVVarying).rgba;

		lowp vec3 color = texColor0.rgb;
		color *= colorVarying;

		gl_FragColor = vec4(color, 1.0);
	}
	);


	BasicShader::BasicShader()
	{}

	BasicShader::~BasicShader()
	{
		DeleteShaderProgram(&program);
	}
	
	void BasicShader::Use()
	{
		Start(&program);
		GL_CHECK
	}

	void BasicShader::Unuse()
	{
		Stop();		
	}

	void BasicShader::LoadShaders()
	{
		CreateShader(&vertexShader, VERT, &pVertex, 1);
		CreateShader(&fragmentShader, FRAG, &pFragment, 1);
		GL_CHECK

		CreateShaderProgram(&program);
		AddShaderToProgram(&program, &vertexShader);
		AddShaderToProgram(&program, &fragmentShader);
		SetAttributeLocation(&program, ATTRIB_VERTEX, "position");
		SetAttributeLocation(&program, ATTRIB_NORMAL, "normal");
		SetAttributeLocation(&program, ATTRIB_TEXTURE_UV, "texUV");

		LinkShaderProgram(&program);		
		GL_CHECK
		my_uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX] = GetUniformLocation(&program, "modelViewProjectionMatrix");
		my_uniforms[UNIFORM_MODEL_MATRIX] = GetUniformLocation(&program, "modelMatrix");
		my_uniforms[UNIFORM_LIGHT_VECTOR] = GetUniformLocation(&program, "lightVec");
		my_uniforms[UNIFORM_TEXTURE_0] = GetUniformLocation(&program, "texture0");
		GL_CHECK
	}

	int BasicShader::LocateUniform(const std::string& name)
	{
		return GetUniformLocation(&program, name.c_str());
	}
}