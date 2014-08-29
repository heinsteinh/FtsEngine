#include "stdafx.h"
#include "matrix_stack.h"


void MatrixStackInitialise(SMatrixStack* const pStack, unsigned int size)
{
	pStack->m_paStack = 0;
	MatrixStackResize(pStack, size);
}

void MatrixStackDestroy(SMatrixStack* const pStack)
{
	if (pStack->m_paStack)
		free(pStack->m_paStack);

	pStack->m_paStack = 0;
}

void MatrixStackResize(SMatrixStack* const pStack, unsigned int size)
{
	if (pStack->m_paStack)
		free(pStack->m_paStack);
	pStack->m_index = 0;
	pStack->m_size = size;
	if (size > 0)
		pStack->m_paStack = (glm::mat4x4*)malloc(sizeof(glm::mat4x4)*pStack->m_size);
	else
		pStack->m_paStack = 0;
}

void MatrixStackPush(SMatrixStack* const pStack)
{
	if (pStack->m_index + 1 < pStack->m_size)
	{
		pStack->m_paStack[pStack->m_index + 1] = pStack->m_paStack[pStack->m_index];
		pStack->m_index++;
	}
}

void MatrixStackPop(SMatrixStack* const pStack)
{
	if (pStack->m_index > 0)
		pStack->m_index -= 1;
}

glm::mat4x4* MatrixStackTop(SMatrixStack* const pStack)
{
	return &pStack->m_paStack[pStack->m_index];
}