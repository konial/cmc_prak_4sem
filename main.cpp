// ����������� ���������� ����� C++
#include <iostream>
#include <cstdio>
#include <cstdlib>

// ���������� OpenGL
#define GLEW_STATIC
#include <GL/glew.h> // ���������� ��� ������������� ������� OpenGL
#include <GLFW/glfw3.h> // ��������� ��� ������ � ������ � ������
#include <SOIL.h> // ���������� ������ � ��������������
// �������������� ����������
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

bool keys[1024];

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat yaw = -90.0f;	// yaw is initialized to -90.0 degrees
					// since a yaw of 0.0 results in a direction
					// vector pointing to the right so we initially
					// rotate a bit to the left.
GLfloat pitch = 0.0f;

GLfloat lastX = 400, lastY = 300;

GLfloat deltaTime = 0.0f;	// �����, ��������� ����� ��������� � ������� ������
GLfloat lastFrame = 0.0f;  	// ����� ������ ���������� �����

bool firstMouse = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
	// � ���������� ����� ����� ���������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // �������� ������� ��������� ������ ��� ������� Y-���������� ���������� � ����� ���� 
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void do_movement()
{
	// Camera controls
	GLfloat cameraSpeed = 5.0f * deltaTime;
	if (keys[GLFW_KEY_W])
		cameraPos += cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_S])
		cameraPos -= cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void test()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	
	//������������� GLFW
	glfwInit();
	//��������� GLFW
	//�������� ����������� ��������� ������ OpenGL. 
	//�������� 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//���������� ����������� ��������� ������� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// ������ ��� ����� ����� ���������� ������� ����� ���������� 
	// ������� ��������� ������� "������� �������"
	glfwSetKeyCallback(window, key_callback);
	// ������ ��� ����� ����� ��������� ���� ����� ���������� 
	// ������� ��������� ������� "�������� ����":
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	//#####################################################################

	//test();

	// ����� ���������� �������� ����������

	GLfloat vertices[] = {
		-0.5f, -0.408f, 0.289f,  -0.3f, 0.0f,
		0.5f, -0.408f, 0.289f,  1.3f, 0.0f,
		0.0f, -0.408f, -0.577f,  0.5f, 1.3f,

		-0.5f, -0.408f, 0.289f,  -0.3f, 0.0f,
		0.5f, -0.408f, 0.289f,  1.3f, 0.0f,
		0.0f, 0.408f, 0.0f,  0.5f, 1.3f,

		-0.5f, -0.408f, 0.289f,  -0.3f, 0.0f,
		0.0f, -0.408f, -0.577f,  1.3f, 0.0f,
		0.0f, 0.408f, 0.0f,  0.5f, 1.3f,

		0.5f, -0.408f, 0.289f,  -0.3f, 0.0f,
		0.0f, -0.408f, -0.577f,  1.3f, 0.0f,
		0.0f, 0.408f, 0.0f,  0.5f, 1.3f
	};

	glm::vec3 tetrahedronPositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//glm::mat4 matrix;
	//matrix = glm::rotate(matrix, 45.0f, glm::vec3(0.1f, 0.0f, 0.0f));
	//matrix = glm::scale(matrix, glm::vec3(0.5f, 0.5f, 0.5f));

	// �������� � ��������� ��������
	int width, height;
	unsigned char *image = SOIL_load_image("pop_art.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	if (!image)
	{
		std::cout << "Failed to load image" << std::endl;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// ������������ ������ � ������� ��������
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// ��������� VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// �������� ��������
	Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

	// ��������� VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	// 1. ����������� VAO
	glBindVertexArray(VAO);
	// 2. �������� ��� ������ ������ � ����� ��� OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. ������������� ��������� �� ��������� � �������� �������� 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	//4. ���������� VAO
	glBindVertexArray(0);

	//#####################################################################

	glm::vec3 direction;
	direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	direction.y = sin(glm::radians(pitch));
	direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	// ������� ����
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//std::cout << 1.0f / deltaTime << std::endl;

		// ��������� �������
		glfwPollEvents();
		do_movement();

		// ������� ������ ������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//cameraPos.x = sin(glfwGetTime()) * 10.0f;
		//cameraPos.z = cos(glfwGetTime()) * 5.0f;

		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glm::mat4 projection;
		projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

		GLuint viewLoc = glGetUniformLocation(shader.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		GLuint projectionLoc = glGetUniformLocation(shader.Program, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		shader.Use();

		// ��������� ������������
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, tetrahedronPositions[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle * (GLfloat)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
			GLuint modelLoc = glGetUniformLocation(shader.Program, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 12);
		}
		glBindVertexArray(0);

		// ������� �����������
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}