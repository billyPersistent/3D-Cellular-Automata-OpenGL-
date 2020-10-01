#include "cell.h"

//populate big vertex array of cells
CellBlock::CellBlock(int blockSize, unsigned int shader)
{
	//set variables
	CellBlock::shader = shader;

	CellBlock::blockSize = blockSize;
	rotation = 0.0f;
	vs = {};
	cs = {};

	//allocate data
	const unsigned int vertexSize = (blockSize * blockSize * blockSize) * 8 * 7;
	const unsigned int indexSize = (blockSize * blockSize * blockSize) * 36;

	vertexData = new float[vertexSize];
	indexData = new unsigned int[indexSize];

	//initialize offsets
	unsigned int vertexOffset = 0;
	unsigned int indexOffset = 0;

	//populate buffers
	for (int xi = 0; xi < blockSize; xi++)
	{
		for (int yi = 0; yi < blockSize; yi++)
		{
			for (int zi = 0; zi < blockSize; zi++)
			{
				//set vertex positions

				vertexData[0 + vertexOffset] = 0.0f + xi - blockSize / 2.0f;
				vertexData[1 + vertexOffset] = 0.0f + yi - blockSize / 2.0f;
				vertexData[2 + vertexOffset] = 0.0f + zi - blockSize / 2.0f;

				vertexData[7 + vertexOffset] = 1.0f + xi - blockSize / 2.0f;
				vertexData[8 + vertexOffset] = 0.0f + yi - blockSize / 2.0f;
				vertexData[9 + vertexOffset] = 0.0f + zi - blockSize / 2.0f;

				vertexData[14 + vertexOffset] = 0.0f + xi - blockSize / 2.0f;
				vertexData[15 + vertexOffset] = 0.0f + yi - blockSize / 2.0f;
				vertexData[16 + vertexOffset] = 1.0f + zi - blockSize / 2.0f;

				vertexData[21 + vertexOffset] = 1.0f + xi - blockSize / 2.0f;
				vertexData[22 + vertexOffset] = 0.0f + yi - blockSize / 2.0f;
				vertexData[23 + vertexOffset] = 1.0f + zi - blockSize / 2.0f;

				vertexData[28 + vertexOffset] = 0.0f + xi - blockSize / 2.0f;
				vertexData[29 + vertexOffset] = 1.0f + yi - blockSize / 2.0f;
				vertexData[30 + vertexOffset] = 0.0f + zi - blockSize / 2.0f;

				vertexData[35 + vertexOffset] = 1.0f + xi - blockSize / 2.0f;
				vertexData[36 + vertexOffset] = 1.0f + yi - blockSize / 2.0f;
				vertexData[37 + vertexOffset] = 0.0f + zi - blockSize / 2.0f;

				vertexData[42 + vertexOffset] = 0.0f + xi - blockSize / 2.0f;
				vertexData[43 + vertexOffset] = 1.0f + yi - blockSize / 2.0f;
				vertexData[44 + vertexOffset] = 1.0f + zi - blockSize / 2.0f;

				vertexData[49 + vertexOffset] = 1.0f + xi - blockSize / 2.0f;
				vertexData[50 + vertexOffset] = 1.0f + yi - blockSize / 2.0f;
				vertexData[51 + vertexOffset] = 1.0f + zi - blockSize / 2.0f;

				//set vertex colors and visible

				for (int vertI = 0; vertI < 8; vertI++)
				{
					//colors
					vertexData[vertI * 7 + 3 + vertexOffset] = 1.0f;
					vertexData[vertI * 7 + 4 + vertexOffset] = 1.0f;
					vertexData[vertI * 7 + 5 + vertexOffset] = 1.0f;

					//visible
					vertexData[vertI * 7 + 6 + vertexOffset] = 0.0f;
				}

				//set indices

				indexData[0 + indexOffset] = 0 + vertexOffset / 7;
				indexData[1 + indexOffset] = 1 + vertexOffset / 7;
				indexData[2 + indexOffset] = 2 + vertexOffset / 7;
				indexData[3 + indexOffset] = 3 + vertexOffset / 7;
				indexData[4 + indexOffset] = 1 + vertexOffset / 7;
				indexData[5 + indexOffset] = 2 + vertexOffset / 7;

				indexData[6 + indexOffset] = 4 + vertexOffset / 7;
				indexData[7 + indexOffset] = 5 + vertexOffset / 7;
				indexData[8 + indexOffset] = 6 + vertexOffset / 7;
				indexData[9 + indexOffset] = 7 + vertexOffset / 7;
				indexData[10 + indexOffset] = 5 + vertexOffset / 7;
				indexData[11 + indexOffset] = 6 + vertexOffset / 7;

				indexData[12 + indexOffset] = 2 + vertexOffset / 7;
				indexData[13 + indexOffset] = 3 + vertexOffset / 7;
				indexData[14 + indexOffset] = 6 + vertexOffset / 7;
				indexData[15 + indexOffset] = 7 + vertexOffset / 7;
				indexData[16 + indexOffset] = 3 + vertexOffset / 7;
				indexData[17 + indexOffset] = 6 + vertexOffset / 7;

				indexData[18 + indexOffset] = 0 + vertexOffset / 7;
				indexData[19 + indexOffset] = 1 + vertexOffset / 7;
				indexData[20 + indexOffset] = 4 + vertexOffset / 7;
				indexData[21 + indexOffset] = 5 + vertexOffset / 7;
				indexData[22 + indexOffset] = 1 + vertexOffset / 7;
				indexData[23 + indexOffset] = 4 + vertexOffset / 7;

				indexData[24 + indexOffset] = 0 + vertexOffset / 7;
				indexData[25 + indexOffset] = 2 + vertexOffset / 7;
				indexData[26 + indexOffset] = 4 + vertexOffset / 7;
				indexData[27 + indexOffset] = 6 + vertexOffset / 7;
				indexData[28 + indexOffset] = 2 + vertexOffset / 7;
				indexData[29 + indexOffset] = 4 + vertexOffset / 7;

				indexData[30 + indexOffset] = 1 + vertexOffset / 7;
				indexData[31 + indexOffset] = 3 + vertexOffset / 7;
				indexData[32 + indexOffset] = 5 + vertexOffset / 7;
				indexData[33 + indexOffset] = 7 + vertexOffset / 7;
				indexData[34 + indexOffset] = 3 + vertexOffset / 7;
				indexData[35 + indexOffset] = 5 + vertexOffset / 7;

				//increment offsets

				vertexOffset += 8 * 7;
				indexOffset += 36;
			}
		}
	}

	//opengl stuff

	vArray = vertexArray();
	vBuffer = vertexBuffer(vertexData, vertexSize * sizeof(float), true, GL_DYNAMIC_DRAW);
	indexBuffer(indexData, indexSize * sizeof(unsigned int), true);

	//positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

	//colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)12);

	//visible
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)24);
}

//destructor
CellBlock::~CellBlock()
{
	delete[] vertexData;
	delete[] indexData;
}

//return boring stuff

unsigned int CellBlock::getVArray()
{
	return vArray;
}

unsigned int CellBlock::getVBuffer()
{
	return vBuffer;
}

unsigned int CellBlock::getShader()
{
	return shader;
}

int CellBlock::getSize()
{
	return blockSize;
}

float* CellBlock::getRotation()
{
	rotationM = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

	return &rotationM[0][0];
}

//return a cell visible at t - 1
bool CellBlock::visible1(int xi, int yi, int zi)
{
	if (xi > -1 and xi < blockSize and
		yi > -1 and yi < blockSize and
		zi > -1 and zi < blockSize)
	{
		int vertexOffset = (xi * (blockSize * blockSize) + yi * (blockSize)+zi) * (8 * 7);

		if (vertexData[vertexOffset + 6] == 0.0f)
		{
			return false;
		}
		return true;
	}
	return false;
}

//returns a cell color at t - 1
glm::vec3 CellBlock::color1(int xi, int yi, int zi)
{
	if (xi > -1 and xi < blockSize and
		yi > -1 and yi < blockSize and
		zi > -1 and zi < blockSize)
	{
		int vertexOffset = (xi * (blockSize * blockSize) + yi * (blockSize)+zi) * (8 * 7);//cubed? idts?

		glm::vec3 color(vertexData[vertexOffset + 3], vertexData[vertexOffset + 4], vertexData[vertexOffset + 5]);
		return color;
	}
	return glm::vec3(0.0f, 0.0f, 0.0f);
}

int CellBlock::neighbors1(int xi, int yi, int zi)
{
	int count = 0;

	for (int xi2 = -1; xi2 <= 1; xi2++)
	{
		for (int yi2 = -1; yi2 <= 1; yi2++)
		{
			for (int zi2 = -1; zi2 <= 1; zi2++)
			{
				if (!(xi2 == 0 and yi2 == 0 and zi2 == 0))
				{
					if (visible1(xi + xi2, yi + yi2, zi + zi2))
					{
						count++;
					}
				}
			}
		}
	}

	return count;
}

int CellBlock::sideNeighbors1(int xi, int yi, int zi)
{
	int count = 0;

	if (visible1(xi + 1, yi, zi)) { count++; }
	if (visible1(xi - 1, yi, zi)) { count++; }
	if (visible1(xi, yi + 1, zi)) { count++; }
	if (visible1(xi, yi - 1, zi)) { count++; }
	if (visible1(xi, yi, zi + 1)) { count++; }
	if (visible1(xi, yi, zi - 1)) { count++; }

	return count;
}

//sets a cell visible at t
void CellBlock::visible2(int xi, int yi, int zi, bool v)
{
	if (xi > -1 and xi < blockSize and
		yi > -1 and yi < blockSize and
		zi > -1 and zi < blockSize)
	{
		SetVis visible = { xi, yi, zi, v };
		vs.push_back(visible);
	}
}

//sets a cell visible at t
void CellBlock::color2(int xi, int yi, int zi, glm::vec3 c)
{
	if (xi > -1 and xi < blockSize and
		yi > -1 and yi < blockSize and
		zi > -1 and zi < blockSize)
	{
		SetColor color = { xi, yi, zi, c };
		cs.push_back(color);
	}
}

//sets a cell visible at t - 1 (private)
void CellBlock::setVisible1(int xi, int yi, int zi, bool v)
{
	int vertexOffset = (xi * (blockSize * blockSize) + yi * (blockSize) + zi) * (8 * 7);

	int visible;
	if (v)
	{
		visible = 1.0f;
	}
	else
	{
		visible = 0.0f;
	}

	for (int vertI = 0; vertI < 8; vertI++)
	{
		vertexData[vertI * 7 + 6 + vertexOffset] = visible;
	}
}

//sets a cell color at t - 1 (private)
void CellBlock::setColor1(int xi, int yi, int zi, glm::vec3 c)
{
	int vertexOffset = (xi * (blockSize * blockSize) + yi * (blockSize)+zi) * (8 * 7);

	for (int vertI = 0; vertI < 8; vertI++)
	{
		//colors
		vertexData[vertI * 7 + 3 + vertexOffset] = c.x;
		vertexData[vertI * 7 + 4 + vertexOffset] = c.y;
		vertexData[vertI * 7 + 5 + vertexOffset] = c.z;
	}
}

//rotate the whole block around the y-axis
void CellBlock::rotate(float degrees)
{
	rotation += degrees;
	rotationM = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
}

//run every frame
void CellBlock::update()
{
	for (int i = 0; i < vs.size(); i++)
	{
		setVisible1(vs[i].xi, vs[i].yi, vs[i].zi, vs[i].visible);
	}
	for (int i = 0; i < cs.size(); i++)
	{
		setColor1(cs[i].xi, cs[i].yi, cs[i].zi, cs[i].color);
	}

	vs.clear();
	cs.clear();

	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, (blockSize * blockSize * blockSize) * 8 * 7 * sizeof(float), vertexData);//optimize with min and max
}

void CellBlock::reset()
{
	int visible = 0.0f;
	glm::vec3 color(1.0f, 1.0f, 1.0f);

	for (int xi = 0; xi < blockSize; xi++)
	{
		for (int yi = 0; yi < blockSize; yi++)
		{
			for (int zi = 0; zi < blockSize; zi++)
			{
				setVisible1(xi, yi, zi, visible);
				setColor1(xi, yi, zi, color);
			}
		}
	}

	rotation = 0.0f;
	vs.clear();
	cs.clear();

	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, (blockSize * blockSize * blockSize) * 8 * 7 * sizeof(float), vertexData);
}

//end of CellBlock class=========================================================================================

void orange_noiseInit(CellBlock& block)
{
	block.visible2(9, 9, 9, true);
	block.color2(9, 9, 9, glm::vec3(1.0f, 1.0f, 0.0f));
	block.update();
}

void orange_noiseRun(CellBlock& block, int xi, int yi, int zi)
{
	if (block.visible1(xi + 1, yi, zi) or block.visible1(xi - 1, yi, zi) or
		block.visible1(xi, yi + 1, zi) or block.visible1(xi, yi - 1, zi) or
		block.visible1(xi, yi, zi + 1) or block.visible1(xi, yi, zi - 1))
	{
		block.visible2(xi, yi, zi, true);

		glm::vec3 color(1.0f - rand() / 400000.0f, 0.7f - rand() / 100000.0f, 0.0f + rand() / 100000.0f);
		block.color2(xi, yi, zi, color);
	}
}

void waterInit(CellBlock& block)
{
	for (int xi = 0; xi < block.getSize(); xi++)
	{
		for (int yi = 0; yi < block.getSize(); yi++)
		{
			for (int zi = 0; zi < block.getSize(); zi++)
			{
				if (yi == 0 or
					(xi >= 6 and xi <= 10 and zi >= 6 and zi <= 10 and yi < 10) or
					((xi == 0 or xi == block.getSize() - 1 or zi == 0 or zi == block.getSize() - 1)
						and yi == 1))//set stone
				{
					block.visible2(xi, yi, zi, true);

					float c;
					if (int(yi / 2.0f) == yi / 2.0f)
					{
						c = 0.4f;
					}
					else
					{
						c = 0.6f;
					}
					block.color2(xi, yi, zi, glm::vec3(c, c, c));
				}
				else if (yi >= block.getSize() - 3)//set water
				{
					block.visible2(xi, yi, zi, true);
					block.color2(xi, yi, zi, glm::vec3(0.3f, 0.3f, 1.0f));
				}
			}
		}
	}
	block.update();
}

void waterRun(CellBlock& block, int xi, int yi, int zi)
{
	if (!block.visible1(xi, yi, zi))//cell empty
	{

	}
	else if (block.color1(xi, yi, zi) == glm::vec3(0.3f, 0.3f, 1.0f))//cell water
	{
		if (!block.visible1(xi, yi - 1, zi))//cell below empty
		{
			block.visible2(xi, yi, zi, false);

			block.visible2(xi, yi - 1, zi, true);
			block.color2(xi, yi - 1, zi, glm::vec3(0.3f, 0.3f, 1.0f));
		}
		else//cell below filled
		{
			//side flow?

			int dir = rand() % 4;

			if (!block.visible1(xi + 1, yi, zi) and dir == 0)
			{
				block.visible2(xi, yi, zi, false);

				block.visible2(xi + 1, yi, zi, true);
				block.color2(xi + 1, yi, zi, glm::vec3(0.3f, 0.3f, 1.0f));
			}
			if (!block.visible1(xi - 1, yi, zi) and dir == 1)
			{
				block.visible2(xi, yi, zi, false);

				block.visible2(xi - 1, yi, zi, true);
				block.color2(xi - 1, yi, zi, glm::vec3(0.3f, 0.3f, 1.0f));
			}
			if (!block.visible1(xi, yi, zi + 1) and dir == 2)
			{
				block.visible2(xi, yi, zi, false);

				block.visible2(xi, yi, zi + 1, true);
				block.color2(xi, yi, zi + 1, glm::vec3(0.3f, 0.3f, 1.0f));
			}
			if (!block.visible1(xi, yi, zi - 1) and dir == 3)
			{
				block.visible2(xi, yi, zi, false);

				block.visible2(xi, yi, zi - 1, true);
				block.color2(xi, yi, zi - 1, glm::vec3(0.3f, 0.3f, 1.0f));
			}
		}
	}
}

void looping_blockInit(CellBlock& block)
{
	
}

void looping_blockRun(CellBlock& block, int xi, int yi, int zi)
{
	bool show = true;
	glm::vec3 color = glm::vec3(glm::distance(glm::vec3(xi, yi, zi), glm::vec3(9.5f, 9.5f, 9.5f)));
	color /= 20;

	if (block.visible1(xi + 1, yi, zi))
	{
		show = !show;
	}
	if (block.visible1(xi - 1, yi, zi))
	{
		show = !show;
	}
	if (block.visible1(xi, yi + 1, zi))
	{
		show = !show;
	}
	if (block.visible1(xi, yi - 1, zi))
	{
		show = !show;
	}
	if (block.visible1(xi, yi, zi + 1))
	{
		show = !show;
	}
	if (block.visible1(xi, yi, zi - 1))
	{
		show = !show;
	}

	block.visible2(xi, yi, zi, show);
	block.color2(xi, yi, zi, color);
}

void looping_block2Init(CellBlock& block)
{
	
}

void looping_block2Run(CellBlock& block, int xi, int yi, int zi)
{
	int n = block.neighbors1(xi, yi, zi);

	bool show;
	glm::vec3 color = glm::vec3(glm::distance(glm::vec3(xi, yi, zi), glm::vec3(9.5f, 9.5f, 9.5f)));
	color /= 20;

	if (n / 2 == n / 2.0f)
	{
		show = true;
	}
	else
	{
		show = false;
	}

	block.visible2(xi, yi, zi, show);
	block.color2(xi, yi, zi, color);
}

void green_gasInit(CellBlock& block)
{
	for (int xi = 0; xi < block.getSize(); xi++)
	{
		for (int yi = 0; yi < block.getSize(); yi++)
		{
			for (int zi = 0; zi < block.getSize(); zi++)
			{
				if (xi < 3 and yi < 3 and zi < 3)
				{
					block.visible2(xi, yi, zi, true);
				}
			}
		}
	}

	block.update();
}

void green_gasRun(CellBlock& block, int xi, int yi, int zi)
{
	int n = block.neighbors1(xi, yi, zi);
	int sn = block.sideNeighbors1(xi, yi, zi);

	bool show;
	glm::vec3 color = glm::vec3(0.0f, n / 26.0f, 0.0f);

	if (sn > 0 and n / 3 == n / 3.0f)
	{
		show = true;
	}
	else
	{
		show = false;
	}

	block.visible2(xi, yi, zi, show);
	block.color2(xi, yi, zi, color);
}

void purple_crystalInit(CellBlock& block)
{
	block.visible2(9, 10, 9, true);
	block.visible2(9, 9, 9, true);
	block.visible2(9, 10, 10, true);
	block.visible2(9, 9, 10, true);
	block.visible2(10, 10, 9, true);
	block.visible2(10, 9, 9, true);
	block.visible2(10, 10, 10, true);
	block.visible2(10, 9, 10, true);

	block.update();
}

void purple_crystalRun(CellBlock& block, int xi, int yi, int zi)
{
	int n = block.neighbors1(xi, yi, zi);
	int sn = block.sideNeighbors1(xi, yi, zi);

	glm::vec3 color = glm::vec3(n / 26.0f, 0.0f, n / 20.0f);

	if (sn == n / 2 and n != 0)
	{
		block.visible2(xi, yi, zi, true);
	}

	block.color2(xi, yi, zi, color);
}

void expanding_blockInit(CellBlock& block)
{
	block.visible2(9, 10, 9, true);
	block.visible2(9, 9, 9, true);
	block.visible2(9, 10, 10, true);
	block.visible2(9, 9, 10, true);
	block.visible2(10, 10, 9, true);
	block.visible2(10, 9, 9, true);
	block.visible2(10, 10, 10, true);
	block.visible2(10, 9, 10, true);

	block.update();
}

void expanding_blockRun(CellBlock& block, int xi, int yi, int zi)
{
	int n = block.neighbors1(xi, yi, zi);
	int sn = block.sideNeighbors1(xi, yi, zi);

	glm::vec3 color = glm::vec3(sn / 8.0f, sn / 8.0f, sn / 6.0f);

	if ((sn == 1 and n > 2) or (sn >= 3))
	{
		block.visible2(xi, yi, zi, true);
	}
	else
	{
		block.visible2(xi, yi, zi, false);
	}

	if (n >= 23)
	{
		block.visible2(xi, yi, zi, false);
	}

	block.color2(xi, yi, zi, color);
}