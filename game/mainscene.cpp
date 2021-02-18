#include "mainscene.h"

MainScene::MainScene() : Scene() {

	std::cout << "\n\n";

	pencils = new EntityEmpty();
	pencils->addSprite("assets/frameTest.tga", 1, 1); //pencils.tga
	pencils->position = Vector2(200, 200);
	addChild(pencils);

	pencils->sprite->frame(0);
}

MainScene::~MainScene() {
	delete pencils;
}

void MainScene::update(float deltaTime) {

	if (input()->getKeyDown(Space)) {
		globals.currentScene = "menu";
	}
}
