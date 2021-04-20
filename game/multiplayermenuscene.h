#ifndef MULTIPLAYERMENUSCENE_H
#define MULTIPLAYERMENUSCENE_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <mvz/scene.h>
#include <mvz/button.h>
#include <mvz/entityempty.h>
#include <mvz/client.h>
#include <mvz/server.h>

class MultiplayerMenuScene : public Scene {

public:
	MultiplayerMenuScene();
	virtual ~MultiplayerMenuScene();
	virtual void update();

private:
	Button* createServerButton;
	Button* joinServerButton;
	Button* backButton;

	void createServer();
	void joinServer();
	void goBack();

	bool isHosting = false;
	bool isJoinig = false;
};

#endif 

