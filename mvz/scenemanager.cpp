#include <mvz/scenemanager.h>

std::string SceneManager::currentScene;
std::map<std::string, Scene*> SceneManager::scenes;

SceneManager::SceneManager(std::map<std::string, Scene*> _scenes, std::string _current) {
	scenes = _scenes;
	currentScene = _current;
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
	scenes[currentScene]->camera->updateViewMatrix(renderer.window());

	//Update entities
	scenes[currentScene]->updateScene();

	//Render entity sprites
	renderer.renderScene(scenes[currentScene]);
}

void SceneManager::switchScene(std::string scene)
{
	SceneManager::currentScene = scene;
	SceneManager::scenes[scene]->onLoad();
}

