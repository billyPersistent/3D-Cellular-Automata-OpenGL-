#include <iostream>

#include <iostream>
#include <chrono>
#include <string.h>

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "input.h"
#include "vertex array.h"
#include "shader.h"

#include "render.h"

int main()
{
	GLFWwindow* window;

	//initialize the GLFW library

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//create a windowed mode window and its OpenGL context

	const float windowWidth = 1200;
	const float windowHeight = 900;

	window = glfwCreateWindow(windowWidth, windowHeight, "Cellular Sim", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//make the window's context current

	glfwMakeContextCurrent(window);

	//check the GLEW library

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew IS NOT ok!!" << std::endl;
	}

	//output OpenGL version
	std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

	//set blend standards

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//initialize variables

	unsigned int FPS = 20;
	auto loopStart = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> loopDur;

	std::string cellChoice;

	//initialize camera

	glm::mat4 projP = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 1.0f, 2000000.0f);
	Camera cam(glm::vec3(0.0f, 0.0f, 50.0f), glm::vec2(0.0f, 0.0f), projP);

	//initialize cell stuff

	unsigned int cellShader = createShader(loadShader("shaders/cellv.shader"), loadShader("shaders/cellf.shader"));
	CellBlock block(20, cellShader);

	//initialize renderer

	Renderer r(&cam);

	//swap buffers
	glfwSwapBuffers(window);

	//unbind all

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);

	while (!glfwWindowShouldClose(window))
	{
		srand(time(NULL));
		block.reset();

		//choice manager
		while (true)
		{
			std::cout << "Choose One: " << std::endl;
			std::cout << "purple_crystal" << std::endl;
			std::cout << "green_gas" << std::endl;
			std::cout << "looping_block" << std::endl;
			std::cout << "looping_block2" << std::endl;
			std::cout << "expanding_block" << std::endl;
			std::cout << "water" << std::endl;
			std::cin >> cellChoice;

			if (cellChoice == "orange_noise")//orange noise case
			{
				orange_noiseInit(block);

				break;
			}
			else if (cellChoice == "water")//water case
			{
				waterInit(block);

				break;
			}
			else if (cellChoice == "looping_block")
			{
				looping_blockInit(block);

				break;
			}
			else if (cellChoice == "looping_block2")
			{
				looping_block2Init(block);

				break;
			}
			else if (cellChoice == "green_gas")
			{
				green_gasInit(block);

				break;
			}
			else if (cellChoice == "purple_crystal")
			{
				purple_crystalInit(block);

				break;
			}
			else if (cellChoice == "expanding_block")
			{
				expanding_blockInit(block);

				break;
			}
			else
			{
				std::cout << "Invalid Choice!" << std::endl << std::endl;
			}
		}

		//main loop
		bool keepRunning = true;
		while (keepRunning and !glfwWindowShouldClose(window))
		{
			loopStart = std::chrono::high_resolution_clock::now();

			//event handling

			//end sim
			if (keyDown(key::ESC))
			{
				keepRunning = false;
			}
			
			//change framerate
			if (keyDown(key::UP) and FPS < 20)
			{
				FPS++;
			}
			if (keyDown(key::DOWN) and FPS > 1)
			{
				FPS--;
			}

			//change rotation
			if (keyDown(key::RIGHT))
			{
				block.rotate(1.5f * (20.0f / FPS));
			}
			if (keyDown(key::LEFT))
			{
				block.rotate(-1.5f * (20.0f / FPS));
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//loop through all cells

			if (!keyDown(key::SPACE))//not paused
			{
				for (int xi = 0; xi < block.getSize(); xi++)
				{
					for (int yi = 0; yi < block.getSize(); yi++)
					{
						for (int zi = 0; zi < block.getSize(); zi++)
						{
							if (cellChoice == "orange_noise")//orange noise case
							{
								orange_noiseRun(block, xi, yi, zi);
							}
							else if (cellChoice == "water")//water case
							{
								waterRun(block, xi, yi, zi);
							}
							else if (cellChoice == "looping_block")
							{
								looping_blockRun(block, xi, yi, zi);
							}
							else if (cellChoice == "looping_block2")
							{
								looping_block2Run(block, xi, yi, zi);
							}
							else if (cellChoice == "green_gas")
							{
								green_gasRun(block, xi, yi, zi);
							}
							else if (cellChoice == "purple_crystal")
							{
								purple_crystalRun(block, xi, yi, zi);
							}
							else if (cellChoice == "expanding_block")
							{
								expanding_blockRun(block, xi, yi, zi);
							}
						}
					}
				}
			}

			r.render(block);
			block.update();

			//swap front and back buffers
			glfwSwapBuffers(window);

			//poll for and process events
			glfwPollEvents();

			//adjust for framerate
			//loopDur = std::chrono::high_resolution_clock::now() - loopStart;
			//std::cout << (loopDur.count() / (1.0f / FPS)) * 100 << "% of alloted time" << std::endl;
			loopDur = std::chrono::high_resolution_clock::now() - loopStart;

			while (loopDur.count() < 1.0f / FPS)
			{
				loopDur = std::chrono::high_resolution_clock::now() - loopStart;
			}
		}

		std::cout << "========================" << std::endl << std::endl;
	}
}