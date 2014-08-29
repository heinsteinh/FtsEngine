#include "stdafx.h"
#include "transforms_gl.h"

/*#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>*/

#include <glm/glm.hpp>
// glm::perspective
//#include <glm/gtc/matrix_projection.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
// glm::value_ptr
#include <glm/gtc/type_ptr.hpp> 

//-------------------------------------------------
// Transforms
//
//
//-------------------------------------------------

//-------------------------------------------------
// Transforms
//
//
//-------------------------------------------------
void TransformInitialise(STransform* const pTransform, unsigned int depth)
{
	MatrixStackInitialise(&pTransform->m_transformStack, depth);
	TransformIdentity(pTransform);
}
void TransformDestroy(STransform* const pTransform)
{
	MatrixStackDestroy(&pTransform->m_transformStack);
}

void TransformResizeStack(STransform* const pTransform, unsigned int depth)
{
	MatrixStackResize(&pTransform->m_transformStack, depth);
}

void TransformPush(STransform*const pTransform)
{
	MatrixStackPush(&pTransform->m_transformStack);
}
void TransformPop(STransform*const pTransform)
{
	MatrixStackPop(&pTransform->m_transformStack);
}

glm::mat4x4* TransformGetCurrentMatrix(STransform*const pTransform)
{
	return MatrixStackTop(&pTransform->m_transformStack);
}

void TransformIdentity(STransform*const pTransform)
{
	*MatrixStackTop(&pTransform->m_transformStack) = glm::mat4(1.0f);	
	//Mtx44Identity(MatrixStackTop(&pTransform->m_transformStack));
}

void TransformTranslate(STransform*const pTransform, const float x, const float y, const float z)
{	
	glm::mat4x4 myMatrix = *MatrixStackTop(&pTransform->m_transformStack);
	*MatrixStackTop(&pTransform->m_transformStack) = glm::translate(myMatrix, glm::vec3(x, y, z));
}

void TransformScale(STransform*const pTransform, const float x, const float y, const float z)
{
	glm::mat4x4 matScale = *MatrixStackTop(&pTransform->m_transformStack);
	*MatrixStackTop(&pTransform->m_transformStack) = glm::scale(matScale, glm::vec3(x, y, z));
	//Mtx44Scale(&MatrixStackTop(&pTransform->m_transformStack), x, y, z);
}

void TransformMultiply(STransform*const pTransform, const glm::mat4x4* const mtx)
{
	
	glm::mat4x4* mat = MatrixStackTop(&pTransform->m_transformStack);
	*MatrixStackTop(&pTransform->m_transformStack) = ((*mat) * (*mtx));
	//Mtx44MultiplyMtx44(MatrixStackTop(&pTransform->m_transformStack), MatrixStackTop(&pTransform->m_transformStack), mtx);
}

void CreateProjectionMatrix(glm::mat4x4* const mat, float l, float r, float b, float t, float n, float f)
{
	glm::mat4x4 proj = {
		//col 1
		(2 * n) / (r - l),
		0,
		0,
		0,
		//col 2
		0,
		(2 * n) / (t - b),
		0,
		0,
		//col 3
		(r + l) / (r - l),
		(t + b) / (t - b),
		-(f + n) / (f - n),
		-1,
		//col 4
		0,
		0,
		-(2 * f*n) / (f - n),
		0
	};
	*mat = proj;
}

void CreateInverseProjectionMatrix(glm::mat4x4* const mat, float l, float r, float b, float t, float n, float f)
{
	glm::mat4x4 proj = {
		//col 1
		(r - l) / (2 * n),
		0,
		0,
		0,
		//col 2
		0,
		(t - b) / (2 * n),
		0,
		0,
		//col 3
		0,
		0,
		0,
		-(f - n) / (2 * f*n),
		//col4
		(r + l) / (2 * n),
		(t + b) / (2 * n),
		-1,
		(f + n) / (2 * f*n)
	};
	*mat = proj;
}

void CreateOrthoMatrix(glm::mat4x4* const mat, float l, float r, float b, float t, float n, float f)
{
	glm::mat4x4 proj = {
		//col 1
		2 / (r - l),
		0,
		0,
		0,
		//col 2
		0,
		2 / (t - b),
		0,
		0,
		//col 3
		0,
		0,
		-2 / (f - n),
		0,
		//col 4
		-(r + l) / (r - l),
		-(t + b) / (t - b),
		-(f + n) / (f - n),
		1
	};
	*mat = proj;
}