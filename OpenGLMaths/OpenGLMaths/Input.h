#pragma once
#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>


class Input 
{
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 position;

	float horizontalAngle;
	float verticalAngle;
public:
	Input();

	float lastTime;

	void computeMatricesFromInputs(GLFWwindow*, GLint, GLint);
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
};