#ifndef MULTIPLAYERSCENE_H
#define MULTIPLAYERSCENE_H

#include <mvz/scene.h>
#include <mvz/button.h>
#include <mvz/entityempty.h>
#include "player.h"

class MultiplayerScene : public Scene {

public:
	MultiplayerScene();
	virtual ~MultiplayerScene();
	virtual void update();

	Button* backButton;
	Player* player;

private:
	void goBack();
};

#endif 

