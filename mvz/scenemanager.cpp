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
	//Update entities
	scenes[globals.currentScene]->updateScene(deltaTime);

	computeMatricesFromInputs(renderer.window(), deltaTime);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render entity sprites
	renderer.renderScene(scenes[globals.currentScene]);

	glfwSwapBuffers(renderer.window());
	glfwPollEvents();
}

