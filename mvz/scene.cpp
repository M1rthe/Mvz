#include <mvz/scene.h>

Scene::Scene() : Entity() {

}

Scene::~Scene() {

}

void Scene::updateScene(float deltaTime) {
	updateEntity(this, deltaTime);
}


void Scene::updateEntity(Entity* entity, float deltaTime)
{
	// call update() for this entity
	entity->update(deltaTime);

	// update() all Children (recursively)
	std::vector<Entity*> children = entity->children;
	std::vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		updateEntity(*child, deltaTime);
	}
}