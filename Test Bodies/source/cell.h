#pragma once

#include <vector>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "vertex array.h"
#include "shader.h"

struct SetVis
{
	int xi, yi, zi;
	bool visible;
};

struct SetColor
{
	int xi, yi, zi;
	glm::vec3 color;
};

class CellBlock
{
private:
	int blockSize;

	float* vertexData;
	unsigned int* indexData;

	unsigned int vArray;
	unsigned int vBuffer;

	unsigned int shader;

	float rotation;
	glm::mat4 rotationM;

	std::vector<SetVis> vs;
	std::vector<SetColor> cs;

	void setVisible1(int xi, int yi, int zi, bool v);
	void setColor1(int xi, int yi, int zi, glm::vec3 c);

public:
	CellBlock(int blockSize, unsigned int shader);
	~CellBlock();

	//get
	unsigned int getVArray();
	unsigned int getVBuffer();
	unsigned int getShader();

	int getSize();
	float* getRotation();

	bool visible1(int xi, int yi, int zi);
	glm::vec3 color1(int xi, int yi, int zi);

	int neighbors1(int xi, int yi, int zi);
	int sideNeighbors1(int xi, int yi, int zi);

	//set
	void visible2(int xi, int yi, int zi, bool v);
	void color2(int xi, int yi, int zi, glm::vec3 c);

	void rotate(float degrees);

	void update();
	void reset();
};

void orange_noiseInit(CellBlock& block);
void orange_noiseRun(CellBlock& block, int xi, int yi, int zi);

void waterInit(CellBlock& block);
void waterRun(CellBlock& block, int xi, int yi, int zi);

void looping_blockInit(CellBlock& block);
void looping_blockRun(CellBlock& block, int xi, int yi, int zi);

void looping_block2Init(CellBlock& block);
void looping_block2Run(CellBlock& block, int xi, int yi, int zi);

void green_gasInit(CellBlock& block);
void green_gasRun(CellBlock& block, int xi, int yi, int zi);

void purple_crystalInit(CellBlock& block);
void purple_crystalRun(CellBlock& block, int xi, int yi, int zi);

void expanding_blockInit(CellBlock& block);
void expanding_blockRun(CellBlock& block, int xi, int yi, int zi);
