#include <mvz/entity.h>

int Entity::nextGuid = 0;

Entity::Entity() {

	guid = nextGuid;
	nextGuid++;

	time = globals.time;
	deltaTime = globals.deltaTime;

	position = Vector3(0.0f, 0.0f, 0.0f);
	rotation = Vector3(0.0f, 0.0f, 0.0f);
	scale = Vector3(1.0f, 1.0f, 1.0f);

	parent = nullptr;
	sprite = nullptr;

	_input = Singleton<Input>::instance();
}

Entity::~Entity() {
	deleteSprite();
	deleteSpriteBatch();
}

void Entity::update() {
	
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

void Entity::addSprite(const std::string& filename, bool grayscale) {
	addSpriteSheet(filename, 1, 1, grayscale);
}

void Entity::addSpriteSheet(const std::string& filename, int u, int v, bool grayscale) {
	deleteSprite();
	sprite = new Sprite(filename, 1.0f / u, 1.0f / v, grayscale);
	spritesWidth = 1.0f / u;
	spritesHeight = 1.0f / v;
}

void Entity::addSpriteGrid(const std::string& filename, int u, int v, int cols, int rows, bool grayscale) {
	
	deleteSpriteBatch();

	spritesWidth = 0;
	spritesHeight = 0;

	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			Sprite* s = new Sprite(filename, 1.0f / u, 1.0f / v, grayscale);
			s->spritePosition.x = x * (s->size.x) + s->size.x / 2;
			s->spritePosition.y = y * (s->size.y) + s->size.y / 2;

			spritebatch.push_back(s);
		}
	}
	spritesWidth = rows * spritebatch[0]->size.x;
	spritesHeight = cols * spritebatch[0]->size.y;
}



