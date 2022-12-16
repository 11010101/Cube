#ifndef __VERTEXARRAY_HPP__
#define __VERTEXARRAY_HPP__

#include <GL/glew.h>

class VertexArray {
private:
	unsigned int vArray;
public:
	VertexArray();
	void ptr(unsigned int index, size_t count, size_t stride, const void* begin, size_t i_activate);
	void Bind() const;
	void UnBind() const;
	~VertexArray();
};

#endif /* __VERTREXARRAY_HPP__ */