#ifndef __VERTEXBUFFER_HPP__
#define __VERTEXBUFFER_HPP__

#include <GL/glew.h>

class VertexBuffer {
private:
	unsigned int vBuffer;
public:
	VertexBuffer(size_t size, const void* data, unsigned int mode);
	void Bind() const;
	void UnBind() const;
	~VertexBuffer();
};

#endif /* __VERTEXBUFFER_HPP__ */