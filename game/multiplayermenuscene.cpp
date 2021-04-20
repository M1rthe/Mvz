#include "multiplayermenuscene.h"

MultiplayerMenuScene::MultiplayerMenuScene() : Scene() {

	backButton = new Button("Back", "assets/button.tga", std::bind(&MultiplayerMenuScene::goBack, this), true);
	backButton->scale = Vector2(3, 3);
	backButton->position = Vector2(-(backButton->sprite->width() * backButton->scale.x / 2) + globals.windowWidth, -(backButton->sprite->height() * backButton->scale.y / 2) + globals.windowHeight);
	addChild(backButton);
	backButton->sprite->color = BLUE;
	backButton->textColor(WHITE);

	std::vector<std::string> createServerText;
	createServerText.push_back("Create");
	createServerText.push_back("Server");

	createServerButton = new Button(createServerText, "assets/button.tga", std::bind(&MultiplayerMenuScene::createServer, this), true);
	createServerButton->scale = Vector2(3, 3); 
	createServerButton->position = Vector2(globals.windowWidth / 2, globals.windowHeight * 0.3);
	createServerButton->sprite->color = RED;
	createServerButton->textColor(WHITE);
	createServerButton->calculatePositions();
	addChild(createServerButton);


	std::vector<std::string> joinServerText;
	joinServerText.push_back("Join");
	joinServerText.push_back("Server");

	joinServerButton = new Button(joinServerText, "assets/button.tga", std::bind(&MultiplayerMenuScene::joinServer, this), true);
	joinServerButton->scale = Vector2(3, 3);
	joinServerButton->position = Vector2(globals.windowWidth / 2, globals.windowHeight * 0.5);
	joinServerButton->sprite->color = RED;
	joinServerButton->textColor(WHITE);
	joinServerButton->calculatePositions();
	addChild(joinServerButton);
}

MultiplayerMenuScene::~MultiplayerMenuScene() {

	removeChild(backButton);
	delete backButton;

	removeChild(createServerButton);
	delete createServerButton;

	removeChild(joinServerButton);
	delete joinServerButton;

	//if (isHosting) 
	//{
	//	delete server;
	//}
}

void MultiplayerMenuScene::update() {

	//if (isHosting)
	//{
	//	server->HandleClients();

	//	if (input()->getKeyDown(KeyCode::H)) {

	//		server->Send("Hi everyone");
	//	}
	//}

	//if (isJoinig)
	//{
	//	std::string message = client->Receive();
	//	if (message.size() > 0) {
	//		std::cout << message << std::endl;
	//	}

	//	if (input()->getKeyDown(KeyCode::H)) {

	//		client->Send("Hello :)");
	//	}
	//}
}

void MultiplayerMenuScene::goBack() {

	isHosting = false;
	isJoinig = false;

	//client->Disconnect();

	//globals.currentScene = "menu";
	switchScene("menu");
}

void MultiplayerMenuScene::createServer() {

	/*server = new Server();
	server->Start(1337);
	server->ListenASync();*/

	isHosting = true;

	//globals.currentScene = "multiplayerSceneHost";
	switchScene("multiplayerSceneHost");
}

void MultiplayerMenuScene::joinServer() {

	//client = new Client();
	//client->Connect("10.112.98.90", 1337); //10.112.98.90       //192.168.178.22

	isJoinig = true;

	//globals.currentScene = "multiplayerSceneJoin";
	switchScene("multiplayerSceneJoin");
}


