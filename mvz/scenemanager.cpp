#include <mvz/scenemanager.h>

SceneManager::SceneManager(std::map<std::string, Scene*> scenesP) {
	scenes = scenesP;
	globals.currentScene = "game";
}

SceneManager::~SceneManager() {

}

void SceneManager::run(Renderer renderer) {

	//Deltatime
	globals.deltaTime = renderer.updateDeltaTime();
	globals.time = glfwGetTime();

	//Update input
	Singleton<Input>::instance()->updateInput(renderer.window());

	//Update Camera
	scenes[globals.currentScene]->camera->updateViewMatrix(renderer.window());

	//Update entities
	scenes[globals.currentScene]->updateScene();

	//Render entity sprites
	renderer.renderScene(scenes[globals.currentScene]);
}

