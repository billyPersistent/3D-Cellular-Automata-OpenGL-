#pragma once

#include "camera.h"

#include "cell.h"

class Renderer
{
private:
	Camera* camera;
public:
	Renderer(Camera* cam);

	void render(CellBlock& block);
};