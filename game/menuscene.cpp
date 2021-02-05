#include "menuscene.h"

MenuScene::MenuScene() : Scene() {

	startButton = new Button(Vector2(0, 0), "Start", "assets/kingkong.tga", std::bind(&MenuScene::start, this));
	addChild(startButton);
}

MenuScene::~MenuScene() {
	removeChild(startButton);
	delete startButton;
}

void MenuScene::update(float deltaTime) {

	if (input()->getKeyDown(Space)) {
		globals.currentScene = "game";
	}
}

void MenuScene::start() {
	std::cout << "start\n";
}

