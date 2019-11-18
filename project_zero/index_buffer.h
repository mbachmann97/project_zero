#pragma once
#include <GL/glew.h>

#include "defines.h"

struct IndexBuffer {
	IndexBuffer(void* data, uint32 numIndices, uint8 elementSize) {
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * elementSize, data, GL_STATIC_DRAW);
	}

	virtual ~IndexBuffer() {
		glDeleteBuffers(1, &bufferId);
	}

	void Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
	}

	void Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

private:
	GLuint bufferId;
};