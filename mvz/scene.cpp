#include <mvz/scene.h>
#include <mvz/scenemanager.h>

Scene::Scene() : Entity() {

	camera = new Camera();
}

Scene::~Scene() {
	delete camera;
}

void Scene::updateScene() {

	updateEntity(this);
}

void Scene::updateEntity(Entity* entity) {

	entity->time = globals.time;
	entity->deltaTime = globals.deltaTime;

	entity->update();

	// update() all Children (recursively)
	std::vector<Entity*> children = entity->children;
	std::vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		updateEntity(*child);
	}
}

void Scene::switchScene(std::string scene)
{
	SceneManager::switchScene(scene);
}