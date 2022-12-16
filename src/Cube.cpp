#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb/stb_image.hpp>

#include <Assertions.hpp>
#include <Shaders.hpp>
#include <VertexBuffer.hpp>
#include <VertexArray.hpp>
#include <IndexBuffer.hpp>
#include <Textures.hpp>

float m_width = 1000.0f / 2.0f;
float m_height = 800.0f / 2.0f;

float yaw = -90.0f; // in the direction you are looking at. if not set to -90.0f the camera will start at the right side and not look at the cube.
float pitch = 0.0f; // just 0 because pitch is already in the middle ( y axis )

glm::vec3 Position(0.0f, 0.0f, 3.0f);
glm::vec3 Up(0.0f, 1.0f, 0.0f);
glm::vec3 unitv(0.0f, 0.0f, -1.0f);
glm::vec3 lPos(2.5f, 2.0f, 0.0f);

bool first = true;

float x = 0.0f, z = 0.0f;

void get(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		lPos.x += 0.01f;
	}
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		lPos.x -= 0.01f;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		lPos.y -= 0.01f;
	}
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		lPos.y += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		lPos.z += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		lPos.z -= 0.01f;
	}
}

void Scroll(GLFWwindow* window, double x, double y);

void walk(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position -= glm::normalize(glm::cross(unitv, Up)) * 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += 0.01f * unitv;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position -= 0.01f * unitv;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += glm::normalize(glm::cross(unitv, Up)) * 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

int main() {
	assert(!glfwInit(), "Failed to init GLFW!\n");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1000, 800, "Cube", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, Scroll);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	assert(glewInit() != GLEW_OK, "Failed to init GLEW!\n");

	float vertices[] = {
		// back
		-1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,		1.0f, 0.0f,		0.0f, 0.0f, -1.0f,

		 // front
		 -1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		 -1.0f,  1.0f, 1.0f,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		  1.0f,  1.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		  1.0f, -1.0f, 1.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		  
		  // bottom
		 -1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		 -1.0f, -1.0f,  1.0f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		  1.0f, -1.0f,  1.0f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		  1.0f, -1.0f, -1.0f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,

		  // top
		  1.0f,  1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		  1.0f,  1.0f,  1.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		 -1.0f,  1.0f,  1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		 -1.0f,  1.0f, -1.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,

		  // left
		 -1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		 -1.0f,  1.0f, -1.0f,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
		 -1.0f,  1.0f,  1.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
		 -1.0f, -1.0f,  1.0f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		  
		  // right
		  1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		  1.0f,  1.0f, -1.0f,		0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
		  1.0f,  1.0f,  1.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
		  1.0f, -1.0f,  1.0f,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		  
	};

	float cube[] = {
		 -1.0f, -1.0f, -1.0f,
		 -1.0f,  1.0f, -1.0f,
		  1.0f,  1.0f, -1.0f,
		  1.0f, -1.0f, -1.0f,

		 -1.0f, -1.0f, 1.0f,
		 -1.0f,  1.0f, 1.0f,
		  1.0f,  1.0f, 1.0f,
		  1.0f, -1.0f, 1.0f,

		 -1.0f, -1.0f, -1.0f,
		 -1.0f, -1.0f,  1.0f,
		  1.0f, -1.0f,  1.0f,
		  1.0f, -1.0f, -1.0f,

		  1.0f,  1.0f, -1.0f,
		  1.0f,  1.0f,  1.0f,
		 -1.0f,  1.0f,  1.0f,
		 -1.0f,  1.0f, -1.0f,

		 -1.0f, -1.0f, -1.0f,
		 -1.0f,  1.0f, -1.0f,
		 -1.0f,  1.0f,  1.0f,
		 -1.0f, -1.0f,  1.0f,

		  1.0f, -1.0f, -1.0f,
		  1.0f,  1.0f, -1.0f,
		  1.0f,  1.0f,  1.0f,
		  1.0f, -1.0f,  1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20,
	};

	Shaders lightShader("Shaders/lightCubeVertex.glsl", "Shaders/lightCubeFragment.glsl");
	VertexBuffer lightBuffer(sizeof(cube), cube, GL_STATIC_DRAW);
	VertexArray lightArray;
	lightArray.ptr(0, 3, 3 * sizeof(float), 0, 0);
	IndexBuffer lightIndex(sizeof(indices), indices, GL_STATIC_DRAW);

	Shaders Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
	VertexBuffer vb(sizeof(vertices), vertices, GL_STATIC_DRAW);
	VertexArray vArray;

	vArray.ptr(0, 3, 8 * sizeof(float), 0, 0);
	vArray.ptr(1, 2, 8 * sizeof(float), (void*)(3 * sizeof(float)), 1);
	vArray.ptr(2, 3, 8 * sizeof(float), (void*)(5 * sizeof(float)), 2);

	IndexBuffer iBuffer(sizeof(indices), indices, GL_STATIC_DRAW);
	Textures Texture("Image/brick.jpg", true);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		get(window);
		walk(window);

		glClearColor(0.1f, 0.01f, 0.19f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);

		glm::mat4 model(1.0f);
		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);

		projection = glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 1.0f, 100.0f);
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		view = glm::lookAt(Position, Position + unitv, Up);

		Shader.Use();
		vb.Bind();
		vArray.Bind();
		iBuffer.Bind();
		Texture.Bind(GL_TEXTURE_2D);

		Shader.m4("model", model);
		Shader.m4("view", view);
		Shader.m4("projection", projection);

		Shader.v3("viewPos", Position);
		Shader.v3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		Shader.v3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		Shader.v3("lightPos", Position + unitv);

		Shader.Draw(GL_TRIANGLES, 39, true);

		lightShader.Use();
		lightBuffer.Bind();
		lightArray.Bind();
		lightIndex.Bind();
		
		model = glm::translate(model, lPos);
		model = glm::scale(model, glm::vec3(0.2f));
		
		lightShader.m4("model", model);
		lightShader.m4("view", view);
		lightShader.m4("projection", projection);
		lightShader.Draw(GL_TRIANGLES, 39, true);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Scroll(GLFWwindow* window, double x, double y) {


	if (first) {
		m_width = x;
		m_height = y;
		first = false;
	}

	float xoffset = x - m_width;
	float yoffset = m_height- y;

	m_width = x;
	m_height = y;

	const float sensitivity = 0.05f;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;


	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 Pos;

	Pos.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	Pos.y = sin(glm::radians(pitch));
	Pos.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	unitv = glm::normalize(Pos);
	
}