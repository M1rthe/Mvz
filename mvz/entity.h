#ifndef ENTITY_H
#define ENTITY_H

#include <mvz/vectorx.h>
#include <mvz/sprite.h>
#include <vector>

class Entity {

public:
	Entity();
	~Entity();
	virtual void update(float deltaTime) = 0;

	Vector3 position; 
	Vector3 rotation;
	Vector3 scale;

	Sprite* sprite;
	std::vector<Entity*> children;

	void addChild(Entity* child);
	void removeChild(Entity* child);
	void addSprite(const std::string& filename);

private:

	void deleteSprite() {
		if (sprite != nullptr) {
			delete sprite;
			sprite = nullptr;
		}
	};

	int guid; 
	static int nextGuid; 
	Entity* parent; 
};

#endif