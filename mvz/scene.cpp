#include <mvz/scene.h>

Scene::Scene() : Entity() {
	camera = new Camera();
	time = globals.time;
}

Scene::~Scene() {
	delete camera;
}

void Scene::updateScene(float deltaTime) {
	updateEntity(this, deltaTime);
}

void Scene::updateEntity(Entity* entity, float deltaTime) {
	
	time = globals.time;

	entity->update(deltaTime);

	// update() all Children (recursively)
	std::vector<Entity*> children = entity->children;
	std::vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		updateEntity(*child, deltaTime);
	}
}