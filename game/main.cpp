// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <mvz/renderer.h>
#include <mvz/camera.h>
#include <mvz/sprite.h>
#include <mvz/entity.h>
#include "mainscene.h"


int main(void)
{
	Renderer renderer(1280, 720);

	MainScene* mainscene = new MainScene();

	while (glfwGetKey(renderer.window(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(renderer.window()) == 0) {

		//Update all entities
		float deltaTime = renderer.updateDeltaTime();
		mainscene->updateScene(deltaTime);

		//Render all enities
		computeMatricesFromInputs(renderer.window(), deltaTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.renderScene(mainscene);
		glfwSwapBuffers(renderer.window());
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed

	delete mainscene;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
