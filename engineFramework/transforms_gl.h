
#include "matrix_stack.h"

#ifndef _TRANSFORMS_H_
#define _TRANSFORMS_H_


typedef struct _STransform
{
	SMatrixStack m_transformStack;
}STransform;

void TransformInitialise(STransform* const, unsigned int depth);
void TransformDestroy(STransform* const);
void TransformResizeStack(STransform* const, unsigned int depth);
void TransformPush(STransform*const);
void TransformPop(STransform*const);
glm::mat4x4* TransformGetCurrentMatrix(STransform*const);

void TransformIdentity(STransform*const);
void TransformTranslate(STransform*const, const float x, const float y, const float z);
void TransformScale(STransform*const, const float x, const float y, const float z);
void TransformMultiply(STransform*const, const glm::mat4x4* const mtx);

//void CreateProjectionMatrix(glm::mat4x4* const mat, float l, float r, float b, float t, float n, float f);
//void CreateInverseProjectionMatrix(glm::mat4x4* const mat, float l, float r, float b, float t, float n, float f);
//void CreateOrthoMatrix(glm::mat4x4* const mat, float l, float r, float b, float t, float n, float f);


#endif //_TRANSFORMS_H_