#include "menuscene.h"

MenuScene::MenuScene() : Scene() {

	startButton = new Button(Vector2(0, 0), "Start", "assets/kingkong.tga", std::bind(&MenuScene::start, this));
	addChild(startButton);

	HEXColor red = Color::RGBA2HEX(RED);
	RGBAColor r = Color::HEX2RGBA(red.hex);
}

MenuScene::~MenuScene() {
	removeChild(startButton);
	delete startButton;
}

void MenuScene::update(float deltaTime) {

	if (input()->getKeyDown(Space)) {
		globals.currentScene = "game";
	}

	std::cout << "Time: "<<time<<"\n";
}

void MenuScene::start() {
	std::cout << "start\n";
}

