#ifndef _GEOMETRY_CREATOR
#define _GEOMETRY_CREATOR

#ifdef __APPLE__
#include "GLUT/glut.h"
#include <OPENGL/gl.h>
#endif

#ifdef __unix__
#include <GL/glut.h>
#endif

#ifdef _WIN32
//#include <GL/glew.h>
//#include <GL/glut.h>
//
//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "OpenGL32.lib")
//#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "freeglut.lib")
#endif

#include "Engine.h"

#include "glm/glm.hpp"
#include <vector>


//https://github.com/jmhain/breakout3d/blob/master/mesh.cpp

struct Mesh
{
	GLuint PositionHandle;
	GLuint NormalHandle;
	GLuint IndexHandle;

	unsigned int IndexBufferLength;

	Mesh();
	Mesh(std::vector<float> const & Positions, std::vector<float> const & Normals, std::vector<unsigned short> const & Indices);
};

class GeometryCreator
{

public:

	static Mesh * CreateQuad(glm::vec3 const & Size = glm::vec3(1.f));

	static Mesh * CreateCube(glm::vec3 const & Size = glm::vec3(1.f));

	static Mesh * CreateCylinder(
		float const baseRadius,
		float const topRadius,
		float const height,
		unsigned int const slices,
		unsigned int const stacks);

	static Mesh * CreateDisc(
		float const innerRadius,
		float const outerRadius,
		float const height,
		unsigned int const slices,
		unsigned int const stacks);

	static Mesh * CreateSphere(
		glm::vec3 const & Radii = glm::vec3(1.f),
		unsigned int const Slices = 32,
		unsigned int const Stacks = 16);

	static Mesh * CreateTorus(
		float const innerRadius,
		float const outerRadius,
		unsigned int const sides,
		unsigned int const rings);

};

#endif