#include <mvz/camera.h>

Camera::Camera() {
	position = Vector3(0, 0, 650);
	rotation = Vector3(0, PI, 0);
	
	direction = glm::vec3(0, 0, -5);
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(1, 0, 0);

	//Orthogonal
	offset = Vector3(1280 / 2, 720 / 2, 0);
	position = Vector3(0, 0, 650) + offset;

	viewMatrix = glm::ortho(0.0, 1280.0, 720.0, 0.0, 0.1, 1000.0);
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

Camera::~Camera() {

}

void Camera::updateViewMatrix(float deltaTime, GLFWwindow* window) {

	direction = glm::vec3(cos(rotation.x) * sin(rotation.y), sin(rotation.x), cos(rotation.x) * cos(rotation.y));
	right = glm::vec3(sin(rotation.y - HALF_PI), 0, cos(rotation.y - HALF_PI));
	right = glm::rotateZ(right, rotation.z*(float)RAD_TO_DEG);
	//glm::rotate(viewMatrix, rotation.z * (float)RAD_TO_DEG, glm::vec3(position.x, position.y, position.z));
	up = glm::cross(right, direction);

	viewMatrix = glm::lookAt(
		glm::vec3(position.x-offset.x, position.y-offset.y, position.z-offset.z), //Position
		glm::vec3(position.x - offset.x + direction.x, position.y - offset.y + direction.y, position.z - offset.z + direction.z), //Look towards Z
		up //Head is up (set to 0,-1,0 to look upside-down) 
	);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}