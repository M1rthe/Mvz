#ifndef SHITTYCAMERA_H
#define SHITTYCAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void computeMatricesFromInputs(GLFWwindow* window, float deltaTime);
glm::mat4 getViewMatrix();
glm::vec3 getCursor();

#endif
