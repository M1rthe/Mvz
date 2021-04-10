//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

#include <mvz/renderer.h>
#include <mvz/camera.h>
#include "mainscene.h"
#include "menuscene.h"
#include "multiplayermenuscene.h"
#include "multiplayerscene.h"
#include <string>
#include <mvz/scene.h>
#include <mvz/scenemanager.h>
#include <map>
#include <mvz/globals.h>

int main(void) {

	Renderer renderer(1280, 720);
	//Renderer renderer(1920, 1080);

	std::map<std::string, Scene*> scenes = {
		{"menu", new MenuScene()},
		{"game", new MainScene()},
		{"multiplayerMenu", new MultiplayerMenuScene()},
		{"multiplayerScene", new MultiplayerScene()}
	};
	//scenes.insert(std::pair<std::string, Scene*>("menu", new MenuScene));

	globals.currentScene = "menu";

	SceneManager* sceneManager = new SceneManager(scenes);

	while (glfwGetKey(renderer.window(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(renderer.window()) == 0) {

		sceneManager->run(renderer);

	} 

	for (std::map<std::string, Scene*>::iterator it = scenes.begin(); it != scenes.end(); ++it) {
		delete it->second;
	}

	delete sceneManager;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}