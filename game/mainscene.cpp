#include "mainscene.h"

MainScene::MainScene() : Scene() {

	pencils = new EntityEmpty();
	pencils->addSprite("assets/frameTest.tga", 2, 1); //pencils.tga
	pencils->position = Vector2(200, 200);
	addChild(pencils);
}

MainScene::~MainScene() {
	delete pencils;
}

void MainScene::update(float deltaTime) {

	if (input()->getKeyDown(Space)) {
		globals.currentScene = "menu";
	}
	if (input()->getKeyDown(F)) {
		pencils->sprite->frame(pencils->sprite->frame() + 1);
	}
}
