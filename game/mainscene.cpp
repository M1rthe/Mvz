#include "mainscene.h"

MainScene::MainScene() : Scene() {

	pencils = new EntityEmpty();
	pencils->addSpriteSheet("assets/frameTest.tga", 2, 1); //pencils.tga
	pencils->position = Vector2(200, 200);
	addChild(pencils);

	tileset = new EntityEmpty();
	tileset->addSpriteGrid("assets/tileset.tga", 8, 8, 4, 4);
	tileset->position = Vector2(300, 200);
	addChild(tileset);
}

MainScene::~MainScene() {

	removeChild(pencils);
	removeChild(tileset);

	delete pencils;
	delete tileset;
}

void MainScene::update() {

	if (input()->getKeyDown(Space)) {
		globals.currentScene = "menu";
	}
	if (input()->getKeyDown(F)) {
		pencils->sprite->frame(pencils->sprite->frame() + 1);
	}
}
