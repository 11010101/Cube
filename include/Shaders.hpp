#ifndef __SHADERS_HPP__
#define __SHADERS_HPP__

#include <fstream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <Assertions.hpp>

class Shaders {
private:
	unsigned int pg;
	unsigned int vs;
	unsigned int fs;
public:
	Shaders(const char *vss, const char *fss);
	void Use() const;
	void UnUse() const;
	void m4(const char* name, const glm::mat4& mat);
	void v3(const char* name, const glm::vec3& vec);
	void Draw(unsigned int mode, size_t count, bool em_ar);
	~Shaders();
private:
	std::string ReadFile(const char* filename);
	void Handle(unsigned int* src, bool s_p);
};

#endif /* __SHADERS_HPP__ */