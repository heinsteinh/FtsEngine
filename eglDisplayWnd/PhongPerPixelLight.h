#pragma once

#include "Shader.h"
#include "Engine.h"
#include "Mesh.h"
#include "Texture.h"
#include "Resource.h"

const char vertexShader[] = STRINGIFY(
	// Vertex shader Phong Shading - Per-pixel lighting
	uniform mat4 uMVPMatrix;
uniform mat4 normalMatrix;

// eye pos
//uniform vec3 eyePos;

// position and normal of the vertices
attribute vec4 aPosition;
attribute vec3 aNormal;

// texture variables
uniform float hasTexture;
attribute vec2 textureCoord;
varying float tex;
varying vec2 tCoord;

// lighting
uniform vec4 lightPos;
uniform vec4 lightColor;

// material
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

// normals to pass on
varying vec3 vNormal;
varying vec3 EyespaceNormal;

varying vec3 lightDir;
varying vec3 eyeVec;

void main() {
	// pass on texture variables
	tex = hasTexture;
	tCoord = textureCoord;

	// normal
	EyespaceNormal = vec3(normalMatrix * vec4(aNormal, 1.0));

	// the vertex position
	vec4 position = uMVPMatrix * aPosition;

	// light dir
	lightDir = lightPos.xyz - position.xyz;
	eyeVec = eyeVec - position.xyz;

	gl_Position = uMVPMatrix * aPosition;
});


const char fragmentShader[] = STRINGIFY(// Frag shader Phong Shading - Per-pixel lighting
	precision mediump float;

// texture variables
uniform sampler2D texture1; // color texture

varying float tex;
varying vec2 tCoord;

varying vec3 vNormal;
varying vec3 EyespaceNormal;

// light
uniform vec4 lightPos;
uniform vec4 lightColor;

// material
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

// eye pos
uniform vec3 eyePos;

// from vertex s
varying vec3 lightDir;
varying vec3 eyeVec;

void main() {
	// Just to show them being used
	//vec4 a = lightPos;
	vec4 b = lightColor;
	vec4 c = matAmbient;
	vec4 d = matDiffuse;
	vec4 e = matSpecular;
	vec3 g = eyePos;
	float f = matShininess;

	vec3 N = normalize(EyespaceNormal);
	vec3 E = normalize(eyeVec);

	vec3 L = normalize(lightDir);

	// Reflect the vector. Use this or reflect(incidentV, N);
	vec3 reflectV = reflect(-L, N);

	// Get lighting terms
	vec4 ambientTerm;
	if (tex >= 1.0) {
		ambientTerm = texture2D(texture1, tCoord);
	}
	else
		ambientTerm = matAmbient * lightColor;

	vec4 diffuseTerm = matDiffuse * max(dot(N, L), 0.0);
	vec4 specularTerm = matSpecular * pow(max(dot(reflectV, E), 0.0), matShininess);

	gl_FragColor = ambientTerm + diffuseTerm + specularTerm;
});

class PhongPerPixelLight : public ANAS::ShaderBase
{

	typedef struct _Material_{
		glm::vec4 diffuseColor;
		glm::vec4 ambientColor;
		glm::vec4 specularColor;
		glm::vec4 emissiveColor;
		float shininess;
	}Material;

	typedef struct _Light_ {
		bool	enabled;
		glm::vec4 diffuseColor;
		glm::vec4 position;
		glm::vec4 specularColor;
		glm::vec4 ambientColor;
	}Light;


	struct MaterialHandle {
		ANAS::Uniform<float, 1>  u_shininess_index;    // index for shininess factor (~30 is good)
		ANAS::Uniform<float, 4>  u_mat_ambient_index;  // index for ambient light color
		ANAS::Uniform<float, 4>  u_mat_diffuse_index;  // index for diffuse light color
		ANAS::Uniform<float, 4>  u_mat_specular_index; // index for specular light color
	};

	struct LightHandle {
		ANAS::Uniform<float, 4>  u_light_position_index;
		ANAS::Uniform<float, 4>  u_light_color_index;
	};

	Light light;
	LightHandle lightHandle;

	Material material;
	MaterialHandle materialHandle;


	ANAS::Uniform<glm::mat4, 4>  u_modelViewProjectionMatrix_index;
	ANAS::Uniform<glm::mat4, 4>  u_normalMatrix_index;


	ANAS::Uniform<float, 3>			u_eye_index;;
	ANAS::Uniform<float, 1>			u_has_texture_index;
	ANAS::Uniform<int, 1>			u_sample_index[4];


	glm::vec3 eye;
	glm::vec3 center;

	
	glm::mat4 matModel;
	glm::mat4 matModelView;
	glm::mat4 matModelViewProj;
	glm::mat4 matNormal;

	GLint positionHandle;
	GLint normalHandle;
	GLint textureHandle;

	bool	bHasTexture;


	// textures enabled?
	bool  enableTexture = true;
	int	 _texIDs[4];	

	typedef std::shared_ptr<CTexture> TexturePtr;
	CTexture*				 texture[4];


	// light parameters
	float shininess;
	glm::vec4 light_direction;
	glm::vec4 light_ambient;
	glm::vec4 light_diffuse;
	glm::vec4 light_specular;

	// angle rotation for light
	float angle = 0.0f;
	bool lightRotate = true;


protected:

	void onInit(){


		GL_CHECK



		//https://github.com/garamsoft/miniproject_1212to1301/blob/441ef0233e5c5d7227a76e477429026a44295839/AndroidShaders/src/graphics/shaders/Renderer.java


		//// extract the indices of the uniforms to use later
		u_modelViewProjectionMatrix_index.Init(this->GetProgram(), "uMVPMatrix");
		u_normalMatrix_index.Init(this->GetProgram(), "normalMatrix");


		positionHandle = glGetAttribLocation(GetProgram(), "aPosition");
		normalHandle = glGetAttribLocation(GetProgram(), "aNormal");
		textureHandle = glGetAttribLocation(GetProgram(), "textureCoord");


		u_has_texture_index.Init(GetProgram(), "hasTexture");

		for (int i = 0; i < sizeof(_texIDs) / sizeof(_texIDs[0]); i++) {
			if (_texIDs[i]>0){

				char tex[15];
				sprintf(tex, "texture%d", (i + 1));
				u_sample_index[i].Init(GetProgram(), tex);
			}
		}


		materialHandle.u_shininess_index.Init(GetProgram(), "matShininess");
		materialHandle.u_mat_ambient_index.Init(GetProgram(), "matAmbient");
		materialHandle.u_mat_diffuse_index.Init(GetProgram(), "matDiffuse");
		materialHandle.u_mat_specular_index.Init(GetProgram(), "matSpecular");

		lightHandle.u_light_position_index.Init(GetProgram(), "lightPos");
		lightHandle.u_light_color_index.Init(GetProgram(), "lightColor");


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

		

		u_has_texture_index.SetValue(bHasTexture ? 2.0f : 0.0f);

		u_modelViewProjectionMatrix_index.SetValue(matModelViewProj);
		u_normalMatrix_index.SetValue(matNormal); //glm::transpose(glm::inverse(glm::mat4(matModelView)))
		
		materialHandle.u_mat_ambient_index.SetValue(material.ambientColor.x, material.ambientColor.y, material.ambientColor.z, material.ambientColor.w);
		materialHandle.u_mat_diffuse_index.SetValue(material.diffuseColor.x, material.diffuseColor.y, material.diffuseColor.z, material.diffuseColor.w);
		materialHandle.u_mat_specular_index.SetValue(material.specularColor.x, material.specularColor.y, material.specularColor.z, material.specularColor.w);
		materialHandle.u_mat_specular_index.SetValue(material.emissiveColor.x, material.emissiveColor.y, material.emissiveColor.z, material.emissiveColor.w);
		materialHandle.u_shininess_index.SetValue(material.shininess);
		
		
		lightHandle.u_light_position_index.SetValue(light.position.x, light.position.y, light.position.z, light.position.w);
		lightHandle.u_light_color_index.SetValue(light.ambientColor.x, light.ambientColor.y, light.ambientColor.z, light.ambientColor.w);
		GL_CHECK

		if (bHasTexture)
		{
			for (int i = 0; i < sizeof(_texIDs) / sizeof(_texIDs[0]); i++)
			{
				if (_texIDs[i]>0)
				{
					
					GL_CHECK
					//glEnable(GL_TEXTURE_2D);
					glActiveTexture(GL_TEXTURE0 + i);
					//LOGI("TEXTURE BIND: %d  %d:\n", i, _texIDs[i]);
					GL_CHECK
					glBindTexture(GL_TEXTURE_2D, _texIDs[i]);

					GL_CHECK
					u_sample_index[i].SetValue(i);
					GL_CHECK
				}

			}
		}
		GL_CHECK
	}

public:

	PhongPerPixelLight() : ANAS::ShaderBase(vertexShader, fragmentShader)
	{
		material.ambientColor  = glm::vec4(0.1, 0.1, 0.1, 1);
		material.diffuseColor  = glm::vec4(0.7, 0.7, 0.7, 1);
		material.emissiveColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		material.specularColor = glm::vec4(2, 2, 2, 1);
		material.shininess = 30.0f;
		
		light.position     = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		light.ambientColor = glm::vec4(2, 2, 2, 1);

		
		bHasTexture = true;
		_texIDs[0] = -1; 
		_texIDs[1] = -1; 
		_texIDs[2] = -1; 
		_texIDs[3] = -1; 


	
		texture[0] = ((ANAS::ResourceItem<CTexture>*)ANAS::Resource::GetInstance().Get("grassTexture"))->Get();
		texture[1] = ((ANAS::ResourceItem<CTexture>*)ANAS::Resource::GetInstance().Get("blendTexture"))->Get();
		texture[2] = ((ANAS::ResourceItem<CTexture>*)ANAS::Resource::GetInstance().Get("rockTexture"))->Get();
		texture[3] = ((ANAS::ResourceItem<CTexture>*)ANAS::Resource::GetInstance().Get("dirtTexture"))->Get();

		
		_texIDs[0] = texture[0]->getTextureId();
		_texIDs[1] = texture[1]->getTextureId();
		_texIDs[2] = texture[2]->getTextureId();
		_texIDs[3] = texture[3]->getTextureId();
					


		matModelViewProj = glm::mat4(1.0f);
		matNormal = glm::mat4(1.0f);

	}


	void setMaterialValue(Material mat_){
		material = mat_;
	}

	void setLightValue(Light light_){
		light = light_;
	}


	

	void SetCamera(glm::vec3 eye, glm::vec3 center)
	{
		this->eye = eye;
		this->center = center;
	}
	

	void DrawMesh(Mesh *mesh, const glm::mat4 &View, const glm::mat4 &Projection)
	{

		//matModel			= glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));

		matModel			= glm::mat4(1.0f);
		matModelView		= View * matModel;
		matModelViewProj	= Projection * matModelView;

		matNormal = glm::transpose(glm::inverse(glm::mat4(matModelView)));

		

		Set();

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

};