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
		{"multiplayerSceneHost", new MultiplayerScene(true)},
		{"multiplayerSceneJoin", new MultiplayerScene(false)}
	};
	//scenes.insert(std::pair<std::string, Scene*>("menu", new MenuScene));

	SceneManager* sceneManager = new SceneManager(scenes, "menu");

	//SceneManager::currentScene = "menu";

	while (glfwGetKey(renderer.window(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(renderer.window()) == 0) {

		sceneManager->run(renderer);
	} 

	delete sceneManager;

	for (std::map<std::string, Scene*>::iterator itr = scenes.begin(); itr != scenes.end(); itr++)
	{
		delete (itr->second);
	}
	scenes.clear();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}