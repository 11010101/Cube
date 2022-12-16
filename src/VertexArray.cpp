#include <VertexArray.hpp>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &vArray);
	glBindVertexArray(vArray);
}

void VertexArray::Bind() const {
	glBindVertexArray(vArray);
}

void VertexArray::UnBind() const {
	glBindVertexArray(0);
}

void VertexArray::ptr(unsigned int index, size_t count, size_t stride, const void* begin, size_t i_activate) {
	glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride, begin);
	glEnableVertexAttribArray(i_activate);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &vArray);
}