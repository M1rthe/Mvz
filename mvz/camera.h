#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include <mvz/vectorx.h>
#include <mvz/globals.h>

class Camera {

public:
	Camera();
	~Camera();

	Vector3 position;
	Vector3 rotation;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	void updateViewMatrix(GLFWwindow* window);

private:

	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 right;
	Vector3 offset;
};

#endif
