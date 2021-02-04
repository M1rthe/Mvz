#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include <mvz/vectorx.h>

class Camera {

public:
	Camera();
	~Camera();

	Vector3 position;
	Vector3 rotation;

private:

};

#endif
