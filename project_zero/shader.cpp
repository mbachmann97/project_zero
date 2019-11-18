#define _CRT_SECURE_NO_DEPRECATE
#include "shader.h"
#include <fstream>
#include <iostream>

Shader::Shader(const char* vertexShaderFilename, const char* fragmentShaderFilename) {
	shaderId = CreateShader(vertexShaderFilename, fragmentShaderFilename);
}

Shader::~Shader() {
	glDeleteProgram(shaderId);
}

void Shader::Bind() {
	glUseProgram(shaderId);
}

void Shader::Unbind() {
	glUseProgram(0);
}

std::string Shader::Parse(const char* filename) {
	FILE* file;
	file = fopen(filename, "rb");
	if (file == nullptr) {
		std::cout << "File " << filename << " not found" << std::endl;
		return 0;
	}

	std::string contents;
	fseek(file, 0, SEEK_END);
	size filesize = ftell(file);
	rewind(file);
	contents.resize(filesize);

	fread(&contents[0], 1, filesize, file);
	fclose(file);

	return contents;
}

GLuint Shader::Compile(std::string shaderSource, GLenum type) {
	GLuint id = glCreateShader(type);
	const char* src = shaderSource.c_str();
	glShaderSource(id, 1, &src, 0);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		int length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Shader compilation error: " << message << std::endl;
		delete[] message;
		return 0;
	}

	return id;
}

GLuint Shader::CreateShader(const char* vertexShaderFilename, const char* fragmentShaderFilename) {
	std::string vertexShaderSource = Parse(vertexShaderFilename);
	std::string fragmentShaderSource = Parse(fragmentShaderFilename);

	GLuint program = glCreateProgram();
	GLuint vs = Compile(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fs = Compile(fragmentShaderSource, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	return program;
}