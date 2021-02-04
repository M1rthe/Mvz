#include <mvz/scenemanager.h>

SceneManager::SceneManager(std::map<std::string, Scene*> scenesP) {
	scenes = scenesP;
	globals.currentScene = "game";
}

SceneManager::~SceneManager() {

}

void SceneManager::run(Renderer renderer) {
	//Update all entities
	float deltaTime = renderer.updateDeltaTime();
	scenes[globals.currentScene]->updateScene(deltaTime);

	//Render all enities
	computeMatricesFromInputs(renderer.window(), deltaTime);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer.renderScene(scenes[globals.currentScene]);
	glfwSwapBuffers(renderer.window());
	glfwPollEvents();
}

