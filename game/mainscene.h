#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <mvz/sprite.h>
#include <mvz/scene.h>
#include <mvz/entity.h>
#include <mvz/entityempty.h>

class MainScene : public Scene {

public:
	MainScene();
	~MainScene();
	virtual void update(float deltaTime);

private:
	EntityEmpty* pencils;
};

#endif 

