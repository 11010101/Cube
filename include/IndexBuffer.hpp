#ifndef __INDEXBUFFER_HPP__
#define __INDEXBUFFER_HPP__

#include <GL/glew.h>

class IndexBuffer {
private:
	unsigned int indexBuffer;
public:
	IndexBuffer(size_t size, const void* data, unsigned int mode);
	void Bind() const;
	void UnBind() const;
	~IndexBuffer();
};

#endif /* __INDEXBUFFER_HPP__ */