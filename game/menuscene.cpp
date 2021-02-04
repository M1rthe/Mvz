#include "menuscene.h"

MenuScene::MenuScene() : Scene() {

	rgba = new EntityEmpty();
	rgba->addSprite("assets/rgba.tga");
	rgba->position = Vector2(700, 500);
	addChild(rgba);
}

MenuScene::~MenuScene() {
	delete rgba;
}

void MenuScene::update(float deltaTime) {
	if (rgba->rotation.z > 6) { rgba->rotation.z = 0; std::cout << "goto menu\n";  globals.currentScene = "game"; }
	rgba->rotation.z += 1 * deltaTime;
}

