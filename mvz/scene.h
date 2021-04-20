#ifndef SCENE_H
#define SCENE_H

#include <mvz/entity.h>
#include <mvz/globals.h>
#include <mvz/camera.h>
#include <mvz/input.h>

class Scene : public Entity {

public:

	Scene();
	virtual ~Scene();
	virtual void onLoad() {}

	Camera* camera;

	void updateScene();

	void switchScene(std::string scene);

private:
	void updateEntity(Entity* entity);
};

#endif