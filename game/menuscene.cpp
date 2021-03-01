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

void MenuScene::update() {

	if (input()->getKeyDown(Space)) {
		globals.currentScene = "game";
	}
}

void MenuScene::start() {
	std::cout << "start game (button)\n";
}

