#include <VertexBuffer.hpp>

VertexBuffer::VertexBuffer(size_t size, const void* data, unsigned int mode) {
	glGenBuffers(1, &vBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, mode);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
}

void VertexBuffer::UnBind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &vBuffer);
}