#include "menuscene.h"

MenuScene::MenuScene() : Scene() {
	
	std::vector<std::string> texts;
	texts.push_back("Start");
	texts.push_back("The");
	texts.push_back("Game");
	
	startButton = new Button(Vector2(0, 0), texts, "assets/kingkong.tga", std::bind(&MenuScene::start, this), true);
	addChild(startButton);
	//startButton->sprite->color = RED;
	startButton->textColor(BLUE);

	rgba = new EntityEmpty();
	rgba->addSprite("assets/rgba.tga");
	rgba->position = Vector2(700, 400);
	addChild(rgba);
}

MenuScene::~MenuScene() {
	removeChild(startButton);
	delete startButton;

	removeChild(rgba);
	delete rgba;
}

void MenuScene::update() {
	rgba->rotation.z += deltaTime;
}

void MenuScene::start() {
	globals.currentScene = "game";
}

