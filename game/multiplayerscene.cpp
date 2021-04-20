#include "multiplayerscene.h"

MultiplayerScene::MultiplayerScene(bool _isHost) : Scene() {

	isHost = _isHost;

	backButton = new Button("Back", "assets/button.tga", std::bind(&MultiplayerScene::goBack, this), true);
	backButton->scale = Vector2(3, 3);
	backButton->position = Vector2(-(backButton->sprite->width() * backButton->scale.x / 2) + globals.windowWidth, -(backButton->sprite->height() * backButton->scale.y / 2) + globals.windowHeight);
	addChild(backButton);
	backButton->sprite->color = BLUE;
	backButton->textColor(WHITE);

	myPlayerSprite = "assets/player.tga";
}

MultiplayerScene::~MultiplayerScene() {

	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
}

void MultiplayerScene::onLoad()
{
	if (isHost)
	{
		server = new Server();
		server->Start(1337);
		server->ListenASync();
	}

	player = new MyMultiPlayer();
	player->addSprite(myPlayerSprite, true);
	player->sprite->color = BLUE;
	player->scale = Vector2(2, 2);
	player->position = Vector2(200, 400);
	addChild(player);

	bool clientSuccesfullyConnected = player->Connect(1337);
	if (!clientSuccesfullyConnected)
	{
		goBack();
	}
}

void MultiplayerScene::update() {

	if (isHost && server != nullptr)
	{
		for (size_t i = 0; i < server->clientConnections.size(); i++)
		{
			std::vector<char> data = server->Receive(server->clientConnections[i]);
			if (data.size() > 0)
			{
				///////////////////////
				PlayerData dataStruct = UnpackNetworkData<PlayerData>(data);
				PlayerDataWithSocket dataStructWithSocket;
				dataStructWithSocket.socket = server->clientConnections[i];
				dataStructWithSocket.posX = dataStruct.posX;
				dataStructWithSocket.posY = dataStruct.posY;
				dataStructWithSocket.scaleX = dataStruct.scaleX;
				dataStructWithSocket.scaleY = dataStruct.scaleY;

				std::vector<char> packetData = PackNetworkData(dataStructWithSocket);

				///////////////////////
				std::cout << "\nSERVER RECV from "<< server->clientConnections[i] <<", SEND to CLIENTS" << std::endl;
				server->SendExcept(server->clientConnections[i], packetData); //data
			}
		}
	}

	if (player != nullptr)
	{
		//if (input()->getKeyDown('H')) {
			//SEND
			struct PlayerData dataStruct;

			dataStruct.posX = player->position.x;
			dataStruct.posY = player->position.y;
			dataStruct.scaleX = player->scale.x;
			dataStruct.scaleY = player->scale.y;
			dataStruct.rotation = player->rotation.z;
			//dataStruct.playerSprite = &myPlayerSprite[0];

			std::cout << "\nCLIENT SEND TO SERVER: " << std::endl;
			std::cout << "posX: " << dataStruct.posX << std::endl;
			std::cout << "posY: " << dataStruct.posY << std::endl;
			std::cout << "scaleX: " << dataStruct.scaleX << std::endl;
			std::cout << "scaleY: " << dataStruct.scaleY << std::endl;
			std::cout << "rotation: " << dataStruct.rotation << std::endl;
			//std::cout << "playerSprite: " << dataStruct.playerSprite << std::endl;

			std::vector<char> packetData = PackNetworkData(dataStruct);
			player->Send(packetData);
		//}

		//Receive
		std::vector<char> data = player->Receive();

		if (data.size() > 0) 
		{
			PlayerDataWithSocket dataStruct = UnpackNetworkData<PlayerDataWithSocket>(data);

			std::cout << "\nPLAYER RECV FROM SERVER: " << std::endl;
			std::cout << "socket: " << dataStruct.socket << std::endl;
			std::cout << "posX: " << dataStruct.posX << std::endl;
			std::cout << "posY: " << dataStruct.posY << std::endl;
			std::cout << "scaleX: " << dataStruct.scaleX << std::endl;
			std::cout << "scaleY: " << dataStruct.scaleY << std::endl;
			std::cout << "rotation: " << dataStruct.rotation << std::endl;

			//clientPlayers.push_back(ClientPlayer(dataStruct.socket));

			bool clientPlayerExists = false;

			for (int i = 0; i < clientPlayers.size(); i++)
			{
				if (clientPlayers[i].socket == dataStruct.socket)
				{
					clientPlayerExists = true;
				}
			}

			if (!clientPlayerExists)
			{
				std::cout << "ClientPlayer doesnt exists, so add new one"<< std::endl;

				clientPlayers.push_back(ClientPlayer(dataStruct.socket));

				clientPlayers[clientPlayers.size() - 1].addSprite(myPlayerSprite, true);
				clientPlayers[clientPlayers.size() - 1].sprite->color = RED;
				addChild(&clientPlayers[clientPlayers.size() - 1]);
			}

			for (int i = 0; i < clientPlayers.size(); i++)
			{
				if (clientPlayers[i].socket == dataStruct.socket)
				{
					std::cout << "ClientPlayer exists, so set data" << std::endl;

					clientPlayers[i].position = Vector2(dataStruct.posX, dataStruct.posY);
					clientPlayers[i].scale = Vector2(dataStruct.scaleX, dataStruct.scaleY);
					clientPlayers[i].rotation.z = dataStruct.rotation;
				}
			}
		
			//std::cout << "playerSprite: " << dataStruct.playerSprite << std::endl;
		}
	}
}

void MultiplayerScene::goBack() {

	if (player != nullptr)
	{
		player->Disconnect();
		removeChild(player);
		//delete player;
		player = nullptr;
	}

	if (isHost)
	{
		server->Disconnect();
		delete server;
		server = nullptr;
	}

	switchScene("multiplayerMenu");
}

