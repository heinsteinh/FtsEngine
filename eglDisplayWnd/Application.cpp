#include "stdafx.h"
#include "Application.h"


#include "Engine.h"
#include "Simple2DShader.h"
#include "PhongShader.h"
#include "PhongPerPixelLight.h"
#include "GouraudShader.h"

#include "ShadeFile.h"
#include "Resource.h"
#include "Mesh.h"

#include "IphoneGraphics.h"
#include "GameLevel.h"
#include "TVertexBuffer.h"


struct StarInfo 
{
	glm::vec3 pos;
	Mesh* mesh;
};

std::vector<StarInfo> mStars;

// create the application here.
Application::Application()
{
	pResource = &ANAS::Resource::GetInstance();

	IphoneGraphics* pIphoneGraphics=  createIphoneGraphics();
	pIphoneGraphics->initExtensions();


	char* data = "TILE";

	typedef struct  vert_
	{
		glm::vec3 pos;
	}vertex;

	vertex vdata;


	vdata.pos = glm::vec3(1.0f, 1.0f, 1.0f);

	TVertexBuffer<vertex*> buffer ;
	buffer.Create(1024);

	buffer.push_back(&vdata);
	buffer.Upload();
}

Application::~Application()
{

}

// Initialize current game.
int Application::Init(const char *resPath)
{


	/*ANAS::ResourceHolder *pHolder = ANAS::Resource::GetInstance().Get("grassTexture");
	texture[0] = ((ANAS::ResourceItem<CTexture>*)pHolder)->Get();*/

	CTexture*	texture[4];
	texture[0] = (new CTexture("C:\\Users\\108012516\\Documents\\Visual Studio 2013\\Projects\\EventSystem2\\eglDisplayWnd\\Images\\grass.tga"));
	texture[1] = (new CTexture("C:\\Users\\108012516\\Documents\\Visual Studio 2013\\Projects\\EventSystem2\\eglDisplayWnd\\Images\\blend.tga"));
	texture[2] = (new CTexture("C:\\Users\\108012516\\Documents\\Visual Studio 2013\\Projects\\EventSystem2\\eglDisplayWnd\\Images\\rock.tga"));
	texture[3] = (new CTexture("C:\\Users\\108012516\\Documents\\Visual Studio 2013\\Projects\\EventSystem2\\eglDisplayWnd\\Images\\dirt.tga"));
	
	
	ANAS::Resource::GetInstance().Set("grassTexture", new ANAS::ResourceItem<CTexture>(texture[0]));
	ANAS::Resource::GetInstance().Set("blendTexture", new ANAS::ResourceItem<CTexture>(texture[1]));
	ANAS::Resource::GetInstance().Set("rockTexture", new ANAS::ResourceItem<CTexture>(texture[2]));
	ANAS::Resource::GetInstance().Set("dirtTexture", new ANAS::ResourceItem<CTexture>(texture[3]));


	



	LOGI("Init File System");
	angle = 0.0;

	pCubeMesh = GeometryCreator::CreateCube(glm::vec3(1.0f));
	matProj = glm::perspective(45.0f, float((float)SCREEN_W / (float)SCREEN_H), 0.1f, 100.0f);
	matView = glm::lookAt(glm::vec3(cos(angle) * 1.7, 2.0, sin(angle) * 1.7), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	

	pPhongShader = new PhongShader;
	pResource->Set("PhongShader", new ANAS::ResourceItem<PhongShader>(pPhongShader));
	pPhongShader->Init();
	pPhongShader->setProjectionMatrix(matProj);


	pSimple2D = new Simple2D(aSimple2DVsh, aSimple2DFsh);
	pResource->Set("SimpleShader", new ANAS::ResourceItem<Simple2D>(pSimple2D));
	pSimple2D->Init();

	
	pPhongPerPixelLight = new PhongPerPixelLight;
	pResource->Set("PhongPerPixelLight", new ANAS::ResourceItem<PhongPerPixelLight>(pPhongPerPixelLight));	
	pPhongPerPixelLight->Init();
		

	pGouraudShader = new GouraudShader;
	pResource->Set("GouraudShader", new ANAS::ResourceItem<GouraudShader>(pGouraudShader));
	pGouraudShader->Init();


	float angle = 0.0f;
	float radius = 6.8f;
	const int starCount = 10;
	for (int i = 0; i < starCount; i++) {
		angle += 0.01f;
		radius += 2.0f / starCount;

		float xr = ((float)(rand() % 10000) / 10000 - 0.5f) * 1.0f;
		float yr = ((float)(rand() % 10000) / 10000 - 0.5f) * radius * 2 / 12;
		float zr = ((float)(rand() % 10000) / 10000 - 0.5f) * 1.0f ;

		float starDim = radius;// ((float)(rand() % 10 + 1));

		StarInfo starInfo;
		starInfo.pos.x = (float)(cosf(angle) * radius + xr);
		starInfo.pos.y = 0.6f + yr;
		starInfo.pos.z = sinf(angle) * radius + zr;
		
		starInfo.mesh = GeometryCreator::CreateCube(glm::vec3(starDim));;

		mStars.push_back(starInfo);
	}


	return true;
}

// Update current state
void Application::Update(float deltatime)
{	
	angle += deltatime *(90 * 3.14f) / 180.0f; 	
	matView = glm::lookAt(glm::vec3(cosf(angle) * 10.0, sinf(angle) * 10.0, 30.0 ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

// Render application
void Application::Render()
{
	//https://github.com/sazameki/ios-gles2.0-sample/blob/master/GLES2.0%20Sample/GLES2.0%20Sample/GameMain.mm

	static int i = 2;
	//glClearColor(0.4f, 1.0f, 0.4f, 0.4f);	
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glClearColor(.0f, .0f, .0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::scale(glm::vec3(1.0, 1.0, 1.0));
	glm::mat4 mvpMat = matView * modelMat;
	pPhongPerPixelLight->DrawMesh(pCubeMesh, mvpMat, matProj);


	for (unsigned int i = 0; i < mStars.size(); i++) {
		const StarInfo& starInfo = mStars[i];
		glm::mat4 modelMat = glm::mat4(1.0f);
		modelMat = glm::translate(starInfo.pos);
		
		glm::mat4 mvpMat = matView * modelMat;
		pPhongPerPixelLight->DrawMesh(starInfo.mesh, mvpMat, matProj);
	}

	i++;
}

// destroy the application here.
void Application::Destroy()
{
	pResource->Release("PhongShader");
	pResource->Release("SimpleShader");
};


