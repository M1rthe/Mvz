#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <mvz/sprite.h>
#include <mvz/scene.h>
#include <mvz/entity.h>
#include <mvz/entityempty.h>
#include <mvz/button.h>
#include "mysingleplayer.h"

class MainScene : public Scene {

public:
	MainScene();
	~MainScene();
	virtual void update();

private:
	Button* backButton;
	MySinglePlayer* player;

	void goBack();
};

#endif 

