#pragma once

#include "Shader.h"



// this is the vertex shader.
// it is called for each corner of each triangle
// it inputs pos and uv from each corner
// it outputs gl_Position, normal_ and uv_ to the rasterizer
// normal_ is the normal in camera space to make calculations easier
const char vertex_shader[] = STRINGIFY(
varying vec2 uv_;
varying vec3 normal_;

attribute vec3 pos;
attribute vec3 normal;
attribute vec2 uv;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 normalMatrix;

void main() {
	uv_ = uv;
	normal_ = (normalMatrix * vec4(normal, 0)).xyz;
	gl_Position = modelViewProjectionMatrix  * vec4(pos, 1.0);
}
);

// this is the fragment shader
// after the rasterizer breaks the triangle into fragments
// this is called for every fragment
// it outputs gl_FragColor, the color of the pixel and inputs normal_ and uv_
// the four samplers give emissive, diffuse, specular and ambient colors
const char fragment_shader[] = STRINGIFY(
precision mediump float;
varying vec2 uv_;
varying vec3 normal_;
uniform vec3 light_direction;
uniform vec4 light_diffuse;
uniform vec4 light_ambient;
uniform vec4 light_specular;
uniform sampler2D samplers[4];
uniform float shininess;

void main() {
	vec3 nnormal = normalize(normal_);
	vec3 half_direction = normalize(light_direction + vec3(0, 0, 1));
	float diffuse_factor = max(dot(light_direction, nnormal), 0.0);
	float specular_factor = pow(max(dot(half_direction, nnormal), 0.0), shininess);
	vec4 diffuse = texture2D(samplers[0], uv_);
	vec4 ambient = texture2D(samplers[1], uv_);
	vec4 emission = texture2D(samplers[2], uv_);
	vec4 specular = texture2D(samplers[3], uv_);
	gl_FragColor =
		ambient * light_ambient +
		diffuse * light_diffuse * diffuse_factor +
		emission +
		specular * light_specular * specular_factor;
}
);

class PhongShader : public ANAS::ShaderBase
{
	//https://github.com/jlamarche/iOS-OpenGLES-Stuff/blob/master/GLKit%20Stuff/GLKReflectionMapEffect%20%26%20GLKSkybox%20Examples/blah/MCViewController.m
	struct Material {
		glm::vec4 diffuseColor;
		glm::vec4 ambientColor;
		glm::vec4 specularColor;
		glm::vec4 emissiveColor;
		float shininess;
	};

	struct Light {
		bool	enabled;
		glm::vec4 diffuseColor;
		glm::vec4 position;
		glm::vec4 specularColor;
		glm::vec4 ambientColor;
	};



	struct MaterialHandle {		
		ANAS::Uniform<float, 1>  u_shininess_index;      // index for shininess factor (~30 is good)
		ANAS::Uniform<float, 4>  u_light_ambient_index;  // index for ambient light color
		ANAS::Uniform<float, 4>  u_light_diffuse_index;  // index for diffuse light color
		ANAS::Uniform<float, 4>  u_light_specular_index; // index for specular light color
	};

	struct LightHandle {
		ANAS::Uniform<float, 3>  u_light_direction_index;		// direction of light in camera space		
	};


	

private:


	ANAS::Uniform<glm::mat4, 4>  u_modelViewProjectionMatrix_index;
	ANAS::Uniform<glm::mat4, 4>  u_normalMatrix_index;
	
	
	

	ANAS::Uniform<float, 1>  u_samplers_index;				// index for texture samplers
	

	glm::mat4 modelViewProjectionMatrix;
	glm::mat4 normalMatrix;
	
	GLuint samplers;

	float shininess;
	glm::vec4 light_direction;
	glm::vec4 light_ambient;
	glm::vec4 light_diffuse;
	glm::vec4 light_specular;
	

	GLint modelMatrixHandle;
	GLint viewMatrixHandle;
	GLint projMatrixHandle;
	

	glm::vec3 eye;
	glm::vec3 center;

	GLint positionHandle;
	GLint normalHandle;
	GLint textureHandle;


	Light light;
	LightHandle lightHandle;
	
	Material currentMaterial;
	MaterialHandle materialHandle;


protected:

	void onInit(){
		

		glGetError();

	
		// extract the indices of the uniforms to use later
		u_modelViewProjectionMatrix_index.Init(this->GetProgram(), "modelViewProjectionMatrix");
		u_normalMatrix_index.Init(this->GetProgram(), "normalMatrix");
	

		u_samplers_index.Init(this->GetProgram(), "samplers");

		positionHandle = glGetAttribLocation(GetProgram(), "pos");
		normalHandle   = glGetAttribLocation(GetProgram(), "normal");
		textureHandle  = glGetAttribLocation(GetProgram(), "uv");
				

		
		lightHandle.u_light_direction_index.Init(this->GetProgram(), "light_direction");

		materialHandle.u_shininess_index.Init(this->GetProgram(), "shininess");
		materialHandle.u_light_ambient_index.Init(this->GetProgram(), "light_ambient");
		materialHandle.u_light_diffuse_index.Init(this->GetProgram(), "light_diffuse");
		materialHandle.u_light_specular_index.Init(this->GetProgram(), "light_specular");

		
		int error;
		if ((error = glGetError()) != GL_NO_ERROR){
			LOGE("Simple2D", "Init error");
			switch (error){
			case GL_INVALID_ENUM:
				LOGE("Simple2D", "GL_INVALID_ENUM");
				break;
			case GL_INVALID_VALUE:
				LOGE("Simple2D", "GL_INVALID_VALUE");
				break;
			case GL_INVALID_OPERATION:
				LOGE("Simple2D", "GL_INVALID_OPERATION");
				break;
			case GL_OUT_OF_MEMORY:
				LOGE("Simple2D", "GL_OUT_OF_MEMORY");
				break;
			}
		}
	}


	void onSet(){

		// Set view matrix
		glm::mat4 view = glm::lookAt(eye, center, glm::vec3(0, 1, 0));
		
		u_modelViewProjectionMatrix_index.SetValue(modelViewProjectionMatrix);
		u_normalMatrix_index.SetValue(normalMatrix);
		

		materialHandle.u_light_ambient_index.SetValue(light_ambient.x, light_ambient.y, light_ambient.z, light_ambient.w);		
		materialHandle.u_light_diffuse_index.SetValue(light_diffuse.x, light_diffuse.y, light_diffuse.z, light_diffuse.w);				
		materialHandle.u_light_specular_index.SetValue(light_specular.x, light_specular.y, light_specular.z, light_specular.w);		
		materialHandle.u_shininess_index.SetValue(shininess);
			
		lightHandle.u_light_direction_index.SetValue(light_direction.x, light_direction.y, light_direction.z);
		
		GL_CHECK
	}




public:
		
	PhongShader() : ANAS::ShaderBase(vertex_shader, fragment_shader){
		light_ambient   = glm::vec4(0.1, 0.1, 0.1, 1);
		light_diffuse   = glm::vec4(0.7, 0.7, 0.7, 1);
		light_direction = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		light_specular  = glm::vec4(2, 2, 2, 1);

		shininess = 30.0f;
	}


	void setLightValue(glm::vec4 diffuse, glm::vec4 ambient, glm::vec4 specular, glm::vec4 direction, float shine){
		light_ambient = ambient;
		light_diffuse = diffuse;
		light_direction = direction;
		light_specular = specular;

	
		shininess = shine;

		modelViewProjectionMatrix = glm::mat4(1.0f);
		normalMatrix = glm::mat4(1.0f);
	}


	void setProjectionMatrix(glm::mat4 matrix){
		modelViewProjectionMatrix = matrix;
	}

	void setNormalMatrix(glm::mat4 matrix){
		normalMatrix = matrix;
	}

	void SetCamera(glm::vec3 eye, glm::vec3 center)
	{
		this->eye = eye;
		this->center = center;
	}

	void MoveLight(glm::vec4 offset)
	{
		light.position += offset;
	}


	void DrawMesh(Mesh *mesh, const glm::mat4 &View, const glm::mat4 &Projection)
	{

		// Set model matrix
		//glUniformMatrix4fv(modelMatrixHandle, 1, false, glm::value_ptr(model));

		glm::mat4 model = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
		glm::mat4 MV = View * model;
	

		onSet();

		glEnableVertexAttribArray(positionHandle);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->PositionHandle);
		glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(normalHandle);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->NormalHandle);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->IndexHandle);

		glDrawElements(GL_TRIANGLES, mesh->IndexBufferLength, GL_UNSIGNED_SHORT, 0);


		glDisableVertexAttribArray(positionHandle);
		glDisableVertexAttribArray(normalHandle);
	}


	void DrawMesh(Mesh *mesh)
	{

		glEnableVertexAttribArray(positionHandle);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->PositionHandle);
		glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(normalHandle);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->NormalHandle);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->IndexHandle);

		glDrawElements(GL_TRIANGLES, mesh->IndexBufferLength, GL_UNSIGNED_SHORT, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(positionHandle);
		glDisableVertexAttribArray(normalHandle);

		GL_CHECK
	}
};

