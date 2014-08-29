#pragma once


#include "TSingleton.h"

#include "Mesh.h"

namespace ANAS{
	class Resource;
}


class GouraudShader;
class PhongPerPixelLight;
class PhongShader;
class Simple2D;
//class Application : public core::CSingleton<Application>
//{
//	friend class core::CSingleton<Application>;

CREATE_SINGLETON(Application)

public:
	// Create the application.
	Application();

	// Destroy the application.
	virtual ~Application();

	// Render current scene.
	virtual void Render();

	// Update Current Scene.
	virtual void Update(float deltatime);

	// Initialize the application.
	virtual int Init(const char *);

	virtual void Destroy();

protected:


	Mesh*			pCubeMesh;
	Simple2D*		pSimple2D;
	PhongShader*	pPhongShader;
	GouraudShader*  pGouraudShader;
	PhongPerPixelLight* pPhongPerPixelLight;
	ANAS::Resource*	pResource;


	glm::mat4 matProj = glm::mat4(1.0f);
	glm::mat4 matView = glm::mat4(1.0f);

	float angle = 0.0;;
};

