#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include <mvz/entity.h>
#include <mvz/scene.h>

class Renderer {

public:

	Renderer(unsigned int w, unsigned int h);
	virtual ~Renderer();

	void renderSprite(Sprite * sprite, float px, float py, float sx, float sy, float rot);
	void renderScene(Scene * scene);
	void renderEntity(Entity * entity);
	GLFWwindow* window() { return _window; };

	unsigned int width() { return window_width; };
	unsigned int height() { return window_height; };

	float updateDeltaTime();

private:

	int init();

	GLFWwindow* _window;
	unsigned int window_width;
	unsigned int window_height;

	GLuint loadShaders(
		const std::string& vertex_file_path,
		const std::string& fragment_file_path
	);

	GLuint programID;

	glm::mat4 projectionMatrix;
};

#endif /* RENDERER_H */
