#include <mvz/entity.h>

int Entity::nextGuid = 0;

Entity::Entity() {

	guid = nextGuid;
	nextGuid++;

	position = Vector3(0.0f, 0.0f, 0.0f);
	rotation = Vector3(0.0f, 0.0f, 0.0f);
	scale = Vector3(1.0f, 1.0f, 1.0f);

	parent = nullptr;
	sprite = nullptr;

	_input = Singleton<Input>::instance();
}

Entity::~Entity() {
	deleteSprite();
}

void Entity::update(float deltaTime) {

}

void Entity::addChild(Entity* child) {
	if (child->parent != nullptr) {
		child->parent->removeChild(child);
	}
	child->parent = this;
	this->children.push_back(child);
}

void Entity::removeChild(Entity* child) {
	std::vector<Entity*>::iterator it = children.begin();
	while (it != children.end()) {
		if ((*it)->guid == child->guid) {
			child->parent = nullptr;
			it = children.erase(it);
		}
		else {
			++it;
		}
	}
}

void Entity::addSprite(const std::string& filename, int u, int v) {
	deleteSprite();
	sprite = new Sprite(filename, 1.0f/u, 1.0f/v);
}

