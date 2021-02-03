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

	//Sprite* pencils = new Sprite("assets/pencils.tga");
	//Sprite* kingkong = new Sprite("assets/kingkong.tga");
	//Sprite* rgba = new Sprite("assets/rgba.tga");

	while (glfwGetKey(renderer.window(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(renderer.window()) == 0) {

		float deltaTime = renderer.updateDeltaTime();
		computeMatricesFromInputs(renderer.window(), deltaTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render all Sprites (Sprite*, xpos, ypos, xscale, yscale, rotation)
		renderer.renderScene(mainscene);
		//renderer.renderSprite(pencils, 400, 300, 1.0f, 1.0f, 0.0f);
		//renderer.renderSprite(kingkong, 900, 400, 1.0f, 1.0f, 0.0f);
		//renderer.renderSprite(rgba, renderer.width() / 2, renderer.height() / 2, 3.0f, 3.0f, 0.0f);

		glfwSwapBuffers(renderer.window());
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed

	//delete pencils;
	//delete kingkong;
	//delete rgba;
	delete mainscene;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
