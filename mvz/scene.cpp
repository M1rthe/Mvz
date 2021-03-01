#include <mvz/scene.h>

Scene::Scene() : Entity() {

	camera = new Camera();
}

Scene::~Scene() {
	delete camera;
}

void Scene::updateScene() {

	time = globals.time;
	deltaTime = globals.deltaTime;

	updateEntity(this);
}

void Scene::updateEntity(Entity* entity) {

	entity->update();

	// update() all Children (recursively)
	std::vector<Entity*> children = entity->children;
	std::vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		updateEntity(*child);
	}
}