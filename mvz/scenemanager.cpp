#include <mvz/scenemanager.h>

SceneManager::SceneManager(std::map<std::string, Scene*> scenesP) {
	scenes = scenesP;
	globals.currentScene = "game";
}

SceneManager::~SceneManager() {

}

void SceneManager::run(Renderer renderer) {

	//Deltatime
	float deltaTime = renderer.updateDeltaTime();

	//Update input
	Singleton<Input>::instance()->updateInput(renderer.window());

	//Update Camera
	scenes[globals.currentScene]->camera->updateViewMatrix(deltaTime, renderer.window());

	//Update entities
	scenes[globals.currentScene]->updateScene(deltaTime);

	//Render entity sprites
	renderer.renderScene(scenes[globals.currentScene]);
}

