#include "menuscene.h"

MenuScene::MenuScene() : Scene() {
	
	singleplayerButton = new Button("Singleplayer", "assets/button.tga", std::bind(&MenuScene::gotoSingleplayer, this), true);
	singleplayerButton->scale = Vector2(5, 3); 
	singleplayerButton->position = Vector2(globals.windowWidth/2, globals.windowHeight * 0.3);
	singleplayerButton->sprite->color = RED;
	singleplayerButton->textColor(WHITE);
	singleplayerButton->calculatePositions();
	addChild(singleplayerButton);

	multiplayerButton = new Button("Multiplayer", "assets/button.tga", std::bind(&MenuScene::gotoMultiplayer, this), true);
	multiplayerButton->scale = Vector2(5, 3); 
	multiplayerButton->position = Vector2(globals.windowWidth / 2, globals.windowHeight * 0.5);
	multiplayerButton->sprite->color = RED;
	multiplayerButton->textColor(WHITE);
	multiplayerButton->calculatePositions();
	addChild(multiplayerButton);

	/*
	rgba = new EntityEmpty();
	rgba->addSprite("assets/rgba.tga");
	rgba->position = Vector2(700, 400);
	addChild(rgba);
	*/
}

MenuScene::~MenuScene() {

	removeChild(singleplayerButton);
	delete singleplayerButton;

	removeChild(multiplayerButton);
	delete multiplayerButton;

	//removeChild(rgba);
	//delete rgba;
}

void MenuScene::update() {
	//rgba->rotation.z += deltaTime;
}

void MenuScene::gotoSingleplayer() {
	//globals.currentScene = "game";
	switchScene("game");
}

void MenuScene::gotoMultiplayer() {
	//globals.currentScene = "multiplayerMenu";
	switchScene("multiplayerMenu");
}

