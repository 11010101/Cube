#include <Textures.hpp>

Textures::Textures(const char* image, bool flip) 
	: data(nullptr), width(0), height(0) {

	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (flip) {
		stbi_set_flip_vertically_on_load(true);
	}
	data = stbi_load(image, &width, &height, 0, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

}

void Textures::Bind(unsigned int to) const {
	glBindTexture(to, Texture);
}

void Textures::UnBind(unsigned int to) const {
	glBindTexture(to, 0);
}

Textures::~Textures() {
	glDeleteTextures(1, &Texture);
}