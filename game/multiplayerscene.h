#ifndef MULTIPLAYERSCENE_H
#define MULTIPLAYERSCENE_H

#include <mvz/scene.h>
#include <mvz/button.h>
#include <mvz/entityempty.h>
#include <mvz/server.h>
#include "clientplayer.h"
#include "mymultiplayer.h"
#include <mvz/data.h>

class MultiplayerScene : public Scene {

public:
	MultiplayerScene(bool isHost);
	virtual ~MultiplayerScene();
	virtual void update();
	virtual void onLoad();

	Button* backButton = nullptr;
	MyMultiPlayer* player = nullptr;

private:
	void goBack();

	bool isHost;
	Server* server = nullptr;
	std::vector<ClientPlayer> clientPlayers;

	std::string myPlayerSprite;

	struct PlayerDataWithSocket : public Data
	{
		enum { TypeCode = 2 };

		SOCKET socket = INVALID_SOCKET;
		float posX = 0;
		float posY = 0;
		float scaleX = 1;
		float scaleY = 1;
		float rotation = 0;
	};

	struct PlayerData : public Data 
	{
		enum { TypeCode = 1 };

		float posX = 0; 
		float posY = 0; 
		float scaleX = 1;
		float scaleY = 1;
		float rotation = 0; 
		//char* playerSprite = "assets/player.tga";
		//std::string playerSprite = "assets/player.tga";
	};
};

#endif 

