#include <Shaders.hpp>

Shaders::Shaders(const char* vss, const char* fss) {
	std::string vf = ReadFile(vss);
	std::string ff = ReadFile(fss);

	const char* vSource = vf.c_str();
	const char* fSource = ff.c_str();

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vSource, 0);
	glCompileShader(vs);
	Handle(&vs, true);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fSource, 0);
	glCompileShader(fs);
	Handle(&fs, true);

	pg = glCreateProgram();
	glAttachShader(pg, vs);
	glAttachShader(pg, fs);

	glLinkProgram(pg);
	Handle(&pg, false);

	glUseProgram(pg);
}

void Shaders::Use() const {
	glUseProgram(pg);
}
void Shaders::UnUse() const {
	glUseProgram(0);
}

void Shaders::m4(const char* name, const glm::mat4& mat) {
	glUniformMatrix4fv(glGetUniformLocation(pg, name), 1, GL_FALSE, (float*)&mat);
}

void Shaders::v3(const char* name, const glm::vec3& vec) {
	glUniform3fv(glGetUniformLocation(pg, name), 1, (float*)&vec);
}

void Shaders::Draw(unsigned int mode, size_t count, bool el_ar) {
	if (el_ar) {
		glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
		return;
	}

	glDrawArrays(mode, 0, count);
}

Shaders::~Shaders() {
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(pg);
}

std::string Shaders::ReadFile(const char* filename) {
	std::ifstream ifile(filename);

	assert(!ifile, "Failed to open %s!\n", filename);

	return { (std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>() };
}

void Shaders::Handle(unsigned int *src, bool s_p) {

	int err;
	char log[512];

	if (s_p) {
		glGetShaderiv(*src, GL_COMPILE_STATUS, &err);
		if (!err) {
			glGetShaderInfoLog(*src, 512, 0, log);
			error("Shader error: %s\n", log);
		}
		return;
	}

	glGetProgramiv(*src, GL_LINK_STATUS, &err);
	if (!err) {
		glGetShaderInfoLog(*src, 512, 0, log);
		error("Program error: %s\n", log);
	}
	return;
}