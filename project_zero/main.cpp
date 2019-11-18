#include <iostream>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "main.h"
#include <cmath>
#include <fstream>

#include "../dependencies/glm/glm.hpp"
#include "../dependencies/glm/ext/matrix_transform.hpp"
#include "../dependencies/glm/gtc/matrix_transform.hpp"
#include "..//dependencies/glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

#include "defines.h"
#include "vertex_buffer.h"
//#include "index_buffer.h"
#include "shader.h"
#include "floating_camera.h"
#include "block.h"
#include "mesh.h"
#include "mapfilehandler.h"
#include <filesystem>
namespace fs = std::experimental::filesystem;

#ifdef _DEBUG

void _GLGetError(const char* file, int line, const char* call) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] " << glewGetErrorString(error) << " in " << file << ":" << line << " Call: " << call << std::endl;
	}
}

#define GLCALL(call) call; _GLGetError(__FILE__, __LINE__, #call)

#else
#define GLCALL(call) call;

#endif

int main(int argc, char** argv) {
	SDL_Window* window;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	uint32 flags = SDL_WINDOW_OPENGL;
	window = SDL_CreateWindow("Project Zero", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		std::cin.get();
		return -1;
	}
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;


	/*uint32 indices[] = {
		0, 1, 2,	// FRONT
		1, 2, 3,	// FRONT
		3, 2, 6,	// RIGHT
		6, 3, 7,	// RIGHT
		7, 6, 4,	// BACK
		4, 7, 5,	// BACK
		5, 4, 0,	// LEFT
		0, 5, 1,	// LEFT
		1, 5, 7,	// TOP
		7, 1, 3,	// TOP
		0, 4, 6,	// BOTTOM
		6, 0, 2		// BOTTOM
	};
	uint32 numIndices = 36;*/

	/*Vertex vertices[]{
			//	 x		y	  z	    u	  v		nx	  ny	 nz
		Vertex{-0.5f, -0.5f, 0.5f, 0.25f, 0.0f, 0.0f, 0.0f, -1.0f},	//FRONT
		Vertex{0.5f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f},	//FRONT
		Vertex{-0.5f, 0.5f, 0.5f, 0.25f, 1.0f, 0.0f, 0.0f, -1.0f},	//FRONT
		Vertex{-0.5f, 0.5f, 0.5f, 0.25f, 1.0f, 0.0f, 0.0f, -1.0f},	//FRONT
		Vertex{0.5f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f},	//FRONT
		Vertex{0.5f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f},	//FRONT
		Vertex{0.5f, 0.5f, 0.5f, 0.25f, 1.0f, 1.0f, 0.0f, 0.0f},	//RIGHT
		Vertex{0.5f, -0.5f, 0.5f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f},	//RIGHT
		Vertex{0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f},	//RIGHT
		Vertex{0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f},	//RIGHT
		Vertex{0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f},	//RIGHT
		Vertex{0.5f, 0.5f, 0.5f, 0.25f, 1.0f, 1.0f, 0.0f, 0.0f},	//RIGHT
		Vertex{0.5f, 0.5f, -0.5f, 0.25f, 1.0f, 0.0f, 0.0f, 1.0f},	//BACK
		Vertex{0.5f, -0.5f, -0.5f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f},	//BACK
		Vertex{-0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f},	//BACK
		Vertex{-0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f},	//BACK
		Vertex{-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f},	//BACK
		Vertex{0.5f, 0.5f, -0.5f, 0.25f, 1.0f, 0.0f, 0.0f, 1.0f},	//BACK
		Vertex{-0.5f, 0.5f, -0.5f, 0.25f, 1.0f, -1.0f, 0.0f, 0.0f},	//LEFT
		Vertex{-0.5f, -0.5f, -0.5f, 0.25f, 0.0f, -1.0f, 0.0f, 0.0f},//LEFT
		Vertex{-0.5f, -0.5f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f},	//LEFT
		Vertex{-0.5f, -0.5f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f},	//LEFT
		Vertex{-0.5f, 0.5f, 0.5f, 0.5f, 1.0f, -1.0f, 0.0f, 0.0f},	//LEFT
		Vertex{-0.5f, 0.5f, -0.5f, 0.25f, 1.0f, -1.0f, 0.0f, 0.0f},	//LEFT
		Vertex{-0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f},	//TOP
		Vertex{0.5f, 0.5f, -0.5f, 0.75f, 1.0f, 0.0f, 1.0f, 0.0f},	//TOP
		Vertex{-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f},	//TOP
		Vertex{0.5f, 0.5f, -0.5f, 0.75f, 1.0f, 0.0f, 1.0f, 0.0f},	//TOP
		Vertex{-0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f},	//TOP
		Vertex{0.5f, 0.5f, 0.5f, 0.75f, 0.0f, 0.0f, 1.0f, 0.0f},		//TOP
		Vertex{-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f},	//BOTTOM
		Vertex{-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f},	//BOTTOM
		Vertex{0.5f, -0.5f, -0.5f, 0.25f, 1.0f, 0.0f, -1.0f, 0.0f},	//BOTTOM
		Vertex{0.5f, -0.5f, -0.5f, 0.25f, 1.0f, 0.0f, -1.0f, 0.0f},	//BOTTOM
		Vertex{0.5f, -0.5f, 0.5f, 0.25f, 0.0f, 0.0f, -1.0f, 0.0f},	//BOTTOM
		Vertex{-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f}	//BOTTOM
	};*/
	/*Block block;
	block.CreateNewBlock(Position{ -0.5f, -0.5f, 0.5f }, 1, 4.0f, 1.0f);
	Vertex* vertices = block.GetVertices();
	uint32 numVertices = 36;*/

	Mesh mesh(MeshSize{ 48, 36, 48 }, Position{-0.5f, -0.5f, 0.5f});
	mesh.GenerateMesh();
	Vertex* vertices = mesh.GetMesh();
	uint64 numVertices = mesh.GetNumVertices();

	Mesh mesh2(MeshSize{ 48, 36, 48 }, Position{ 47.5f, -0.5f, 0.5f});
	mesh2.GenerateMesh();
	Vertex* vertices2 = mesh2.GetMesh();
	uint32 numVertices2 = mesh2.GetNumVertices();


	Mesh mesh3(MeshSize{ 48, 36, 48 }, Position{ 47.5f, -0.5f, -47.5f });
	mesh3.GenerateMesh();
	Vertex* vertices3 = mesh3.GetMesh();;
	uint32 numVertices3 = mesh3.GetNumVertices();


	Mesh mesh4(MeshSize{ 48, 36, 48 }, Position{ -0.5f, -0.5f, -47.5f });
	mesh4.GenerateMesh();
	Vertex* vertices4 = mesh4.GetMesh();
	uint32 numVertices4 = mesh4.GetNumVertices();

	/*fs::create_directory("./mapdata");
	std::string path = "./";
	for (const auto& entry : fs::directory_iterator(path))
		std::cout << entry.path() << std::endl;*/

	MapFileHandler mfh;
	/*mfh.CalcMesh();
	std::vector<Vertex> vertices = mfh.GetV1();
	std::vector<Vertex> vertices2 = mfh.GetV2();
	std::vector<Vertex> vertices3 = mfh.GetV3();
	std::vector<Vertex> vertices4 = mfh.GetV4();
	uint64 numVertices = mfh.GetNumVertices();*/
	mfh.WriteToFile(vertices, vertices2, vertices3, vertices4, numVertices);

	VertexBuffer vertexBuffer(vertices , numVertices);
	vertexBuffer.Unbind();
	VertexBuffer vertexBuffer2(vertices2, numVertices);
	vertexBuffer.Unbind();
	VertexBuffer vertexBuffer3(vertices3, numVertices);
	vertexBuffer.Unbind();
	VertexBuffer vertexBuffer4(vertices4, numVertices);
	vertexBuffer.Unbind();



	//IndexBuffer indexBuffer(indices, numIndices, sizeof(indices[0]));

	int32 textureWidth = 0;
	int32 textureHeight = 0;
	int32 bitsPerPixel = 0;
	stbi_set_flip_vertically_on_load(true);
	auto textureBuffer = stbi_load("graphics/grassblock.png", &textureWidth, &textureHeight, &bitsPerPixel, 4);

	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (textureBuffer) {
		stbi_image_free(textureBuffer);
	}

	Shader shader("basic.vert", "basic.frag");
	shader.Bind();
	int directionLocation = glGetUniformLocation(shader.getShaderId(), "u_directional_light.direction");
	glm::vec3 sunColor = glm::vec3(1.0f);
	glm::vec3 sunDirection = glm::vec3(-1.0f);
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_directional_light.diffuse"), 1, (float*)&sunColor);
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_directional_light.specular"), 1, (float*)&sunColor);
	sunColor *= 0.2f;
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_directional_light.ambient"), 1, (float*)&sunColor);

	uint64 perfCounterFrequency = SDL_GetPerformanceFrequency();
	uint64 lastCounter = SDL_GetPerformanceCounter();
	float32 delta = 0.0f;

	//bind color uniform
	int colorUniformLocation = glGetUniformLocation(shader.getShaderId(), "u_color");
	if (!colorUniformLocation != -1) {
		glUniform4f(colorUniformLocation, 1.0f, 0.0f, 1.0f, 1.0f);
	}

	//bind texture uniform
	int textureUniformLocation = glGetUniformLocation(shader.getShaderId(), "u_texture");
	if (!textureUniformLocation != -1) {
		glUniform1i(textureUniformLocation, 0);
	}

	//create Matrices

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(1.2f));

	FloatingCamera camera(90.0f, 800.0f, 600.0f);
	camera.Translate(glm::vec3(0.0f, 0.0f, 5.0f));
	camera.Update();

	glm::mat4 modelViewProj = camera.GetViewProj() * model;

	//bind model matrix uniform
	int modelViewProjMatrixLocation = glGetUniformLocation(shader.getShaderId(), "u_modelViewProj");
	int modelViewLocation = glGetUniformLocation(shader.getShaderId(), "u_modelView");
	int invModelViewLocation = glGetUniformLocation(shader.getShaderId(), "u_invModelView");

	// -> Wireframe Mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	bool buttonW = false;
	bool buttonS = false;
	bool buttonA = false;
	bool buttonD = false;
	bool buttonSpace = false;
	bool buttonShift = false;

	float32 cameraSpeed = 12.0f;

	//GAME LOOP START
	float32 time = 0.0f;
	bool close = false;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	while (!close) {

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				close = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_w:
					buttonW = true;
					break;
				case SDLK_s:
					buttonS = true;
					break;
				case SDLK_a:
					buttonA = true;
					break;
				case SDLK_d:
					buttonD = true;
					break;
				case SDLK_SPACE:
					buttonSpace = true;
					break;
				case SDLK_LSHIFT:
					buttonShift = true;
					break;
				case SDLK_ESCAPE:
					SDL_SetRelativeMouseMode(SDL_FALSE);
					break;
				}
			}
			else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_w:
					buttonW = false;
					break;
				case SDLK_s:
					buttonS = false;
					break;
				case SDLK_a:
					buttonA = false;
					break;
				case SDLK_d:
					buttonD = false;
					break;
				case SDLK_SPACE:
					buttonSpace = false;
					break;
				case SDLK_LSHIFT:
					buttonShift = false;
					break;
				}
			}
			else if (event.type == SDL_MOUSEMOTION) {
				if(SDL_GetRelativeMouseMode())
					camera.OnMouseMoved(event.motion.xrel, event.motion.yrel);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT)
					SDL_SetRelativeMouseMode(SDL_TRUE);
			}
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		time += delta;

		if (buttonW) {
			camera.MoveFront(delta * cameraSpeed);
		}
		if (buttonS) {
			camera.MoveFront(-delta * cameraSpeed);
		}
		if (buttonA) {
			camera.MoveSideways(-delta * cameraSpeed);
		}
		if (buttonD) {
			camera.MoveSideways(delta * cameraSpeed);
		}
		if (buttonSpace) {
			camera.MoveUp(delta * cameraSpeed);
		}
		if (buttonShift) {
			camera.MoveUp(-delta * cameraSpeed);
		}

		if (!colorUniformLocation != -1) {
			glUniform4f(colorUniformLocation, cosf(time)*cosf(time), 0.0f, 1.0f, 1.0f);
		}

		camera.Update();
		//model = glm::rotate(model, 1.0f * delta, glm::vec3(0, 1, 0));
		modelViewProj = camera.GetViewProj() * model;
		glm::mat4 modelView = camera.GetView() * model;
		glm::mat4 invModelView = glm::transpose(glm::inverse(modelView));

		glm::vec4 transformedSunDirection = glm::transpose(glm::inverse(camera.GetView())) * glm::vec4(sunDirection, 1.0f);
		glUniform3fv(directionLocation, 1, (float*)&transformedSunDirection);

		vertexBuffer.Bind();
		//indexBuffer.Bind();
		glUniformMatrix4fv(modelViewProjMatrixLocation, 1, GL_FALSE, &modelViewProj[0][0]);
		glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &modelView[0][0]);
		glUniformMatrix4fv(invModelViewLocation, 1, GL_FALSE, &invModelView[0][0]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		//GLCALL(glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0));
		//indexBuffer.Unbind();
		vertexBuffer.Unbind();

		vertexBuffer2.Bind();
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		vertexBuffer2.Unbind();

		vertexBuffer3.Bind();
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		vertexBuffer3.Unbind();

		vertexBuffer4.Bind();
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		vertexBuffer4.Unbind();

		SDL_GL_SwapWindow(window);

		//calc delta and FPS
		uint64 endCounter = SDL_GetPerformanceCounter();
		uint64 counterElapsed = endCounter - lastCounter;
		delta = ((float32)counterElapsed) / (float32)perfCounterFrequency;
		uint32 FPS = (uint32)((float32)perfCounterFrequency / (float32)counterElapsed);
		//std::cout << FPS << std::endl;
		lastCounter = endCounter;
	}

	glDeleteTextures(1, &textureId);

	return 0;
}