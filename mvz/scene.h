#ifndef SCENE_H
#define SCENE_H

#include <mvz/entity.h>

class Scene : public Entity {

public:
	Scene();
	~Scene();

	void updateScene(float deltaTime);

private:
	void updateEntity(Entity* entity, float deltaTime);
};

#endif