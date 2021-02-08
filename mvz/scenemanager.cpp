#include <mvz/scenemanager.h>

SceneManager::SceneManager(std::map<std::string, Scene*> scenesP) {
	scenes = scenesP;
	globals.currentScene = "menu";
}

SceneManager::~SceneManager() {

}

void SceneManager::run(Renderer renderer) {

	//Deltatime
	float deltaTime = renderer.updateDeltaTime();

	//Update entities
	scenes[globals.currentScene]->updateScene(deltaTime);

	//Update Camera
	scenes[globals.currentScene]->camera->updateViewMatrix(deltaTime, renderer.window());
	//std::cout << "update view matrix of scene["<< globals.currentScene <<"]\n";
	//computeMatricesFromInputs(renderer.window(), deltaTime);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Update input
	Singleton<Input>::instance()->updateInput(renderer.window());

	//Render entity sprites
	renderer.renderScene(scenes[globals.currentScene]);

	glfwSwapBuffers(renderer.window());
	glfwPollEvents();
}

