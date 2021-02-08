#ifndef SCENE_H
#define SCENE_H

#include <mvz/entity.h>
#include <mvz/globals.h>
#include <mvz/camera.h>
#include <mvz/input.h>

class Scene : public Entity {

public:

	Scene();
	~Scene();

	Camera* camera;

	void updateScene(float deltaTime);

private:
	void updateEntity(Entity* entity, float deltaTime);
};

#endif