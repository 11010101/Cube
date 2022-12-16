#ifndef __TEXTURES_HPP__
#define __TEXTURES_HPP__

#include <GL/glew.h>
#include <stb/stb_image.hpp>

class Textures {
private:
	unsigned int Texture;
	unsigned char* data;
	int width;
	int height;
public:
	Textures(const char* image, bool flip);
	void Bind(unsigned int to) const;
	void UnBind(unsigned int to) const;
	~Textures();
};

#endif /* __TEXTURES_HPP__ */