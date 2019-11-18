#pragma once
#include <GL/glew.h>

#include "defines.h"
#include <cstdint>

struct UVBuffer {

	UVBuffer(void* data, uint32 numUV) {
		glGenBuffers(1, &bufferId);
		//glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, numUV * sizeof(UV), data, GL_STATIC_DRAW);
	
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UV), (void*)offsetof(UV, u));
	}

	virtual ~UVBuffer() {
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
