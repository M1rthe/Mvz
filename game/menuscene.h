#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <mvz/sprite.h>
#include <mvz/scene.h>
#include <mvz/entity.h>
#include <mvz/entityempty.h>

class MenuScene : public Scene {

public:
	MenuScene();
	~MenuScene();
	virtual void update(float deltaTime);

private:
	EntityEmpty* rgba;
};

#endif 

