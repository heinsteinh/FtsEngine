
#ifndef _MATRIX_STACK_H_
#define _MATRIX_STACK_H_

#include <glm\matrix.hpp>


typedef struct _SMatrixStack
{
	unsigned int	m_index;
	unsigned int	m_size;
	glm::mat4x4*  	m_paStack;
}SMatrixStack;

void MatrixStackInitialise(SMatrixStack* const pStack, unsigned int size);
void MatrixStackDestroy(SMatrixStack* const pStack);
void MatrixStackResize(SMatrixStack* const pStack, unsigned int size);
void MatrixStackPush(SMatrixStack* const pStack);
void MatrixStackPop(SMatrixStack* const pStack);
glm::mat4x4* MatrixStackTop(SMatrixStack* const pStack);

#endif// _MATRIX_STACK_H_