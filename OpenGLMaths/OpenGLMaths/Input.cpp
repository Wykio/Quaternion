#pragma once
#define GLEW_STATIC 1	
#include <glew.h>
#include <glfw3.h>
#include "Input.h"
#include "Vec3.h"

Input::Input()
{
	ViewMatrix = glm::mat4();
	ProjectionMatrix = glm::mat4();

	direction = glm::vec3();
	right = glm::vec3();
	up = glm::vec3();
	position = glm::vec3();

	horizontalAngle = 3.14f;
	verticalAngle = 3.14f;
}

void Input::computeMatricesFromInputs(GLFWwindow* win, GLint winWidth, GLint winHeight)
{
	float speed = 5.0f;
	float mouseSpeed = 0.5f;

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;

	double xpos, ypos;
	glfwGetCursorPos(win, &xpos, &ypos);

	glfwSetCursorPos(win, winWidth / 2, winHeight / 2);

	horizontalAngle -= mouseSpeed * deltaTime * float(winWidth / 2 - xpos);
	verticalAngle += mouseSpeed * deltaTime * float(winHeight / 2 - ypos);

	//Position
	//Forward
	if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// Backward
	if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// Right
	if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// Left
	if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
		horizontalAngle += mouseSpeed * deltaTime * float(winWidth / 2 - 100);
	}
	if (glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS) {
		rotation = Vec3(1, 0, 0);
	}
	if (glfwGetKey(win, GLFW_KEY_O) == GLFW_PRESS) {
		rotation = Vec3(0, 1, 0);
	}
	if (glfwGetKey(win, GLFW_KEY_I) == GLFW_PRESS) {
		rotation = Vec3(0, 0, 1);
	}
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwDestroyWindow(win);
		exit(0);
	}
	
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	up = glm::cross(right, direction);

	//Matrix
	ProjectionMatrix = glm::perspective(glm::radians(45.f), float(winWidth) / float(winHeight), 0.01f, 1000.0f);
	
	ViewMatrix = glm::lookAt(
		position,
		position + direction,
		up
	);
}

glm::mat4 Input::getProjectionMatrix()
{
	return ProjectionMatrix;
}

glm::mat4 Input::getViewMatrix()
{
	return ViewMatrix;
}
