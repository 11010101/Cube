#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec2 Textures;
out vec3 FragPos;

void main() {

	FragPos = vec3(model * vec4(Position, 1.0f));

	gl_Position = projection * view * model * vec4(Position, 1.0);
	Textures = TexCoords;
	Normal = Normals;
}