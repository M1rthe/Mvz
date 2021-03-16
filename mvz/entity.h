#ifndef ENTITY_H
#define ENTITY_H

#include <mvz/vectorx.h>
#include <mvz/sprite.h>
#include <mvz/input.h>
#include <vector>
#include <mvz/singleton.h>
#include <mvz/globals.h>

#include <iostream>
#include <cstdlib> 
#include <ctime> 

class Entity {

public:
	Entity();
	~Entity();
	virtual void update();

	double time;
	double deltaTime;

	Vector3 position; 
	Vector3 rotation;
	Vector3 scale;

	Sprite* sprite;
	std::vector<Sprite*> spritebatch;

	int spritesWidth = 0;
	int spritesHeight = 0;

	std::vector<Entity*> children;

	void addChild(Entity* child);
	void removeChild(Entity* child);
	void addSprite(const std::string& filename);
	void addSpriteSheet(const std::string& filename, int u, int v);
	void addSpriteGrid(const std::string& filename, int u, int v, int cols, int rows);

	Input* input() { return _input; };

private:

	void deleteSprite() {
		if (sprite != nullptr) {
			delete sprite;
			sprite = nullptr;
		}
	};

	void deleteSpriteBatch() {
		int s = spritebatch.size();
		for (int i = 0; i < s; i++) {
			delete spritebatch[i];
		}
		spritebatch.clear();
	};

	int guid; 
	static int nextGuid; 
	Entity* parent; 

	Input* _input;
};

#endif