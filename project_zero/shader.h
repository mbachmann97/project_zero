#pragma once
#include <string>

#include <GL/glew.h>
#include "defines.h"

class Shader {
public:
	Shader(const char* vertexShaderFilename, const char* fragmentShaderFilename);
	virtual ~Shader();

	void Bind();
	void Unbind();

	GLuint getShaderId() {
		return shaderId;
	}

private:

	GLuint Compile(std::string shaderSource, GLenum type);
	std::string Parse(const char* filename);
	GLuint CreateShader(const char* vertexShaderFilename, const char* fragmentShaderFilename);

	GLuint shaderId;
};

