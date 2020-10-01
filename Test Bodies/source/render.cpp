#include "render.h"

Renderer::Renderer(Camera* cam)
{
	camera = cam;
}

void Renderer::render(CellBlock& block)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glUseProgram(block.getShader());
	glBindVertexArray(block.getVArray());
	glBindBuffer(GL_ARRAY_BUFFER, block.getVBuffer());

	int rotationLocation = glGetUniformLocation(block.getShader(), "u_Rotation");
	glUniformMatrix4fv(rotationLocation, 1, GL_FALSE, block.getRotation());

	int matrixLocation = glGetUniformLocation(block.getShader(), "u_Camera");
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, camera->getMatrix());

	glDrawElements(GL_TRIANGLES, 36 * (block.getSize() * block.getSize() * block.getSize()), GL_UNSIGNED_INT, nullptr);
}