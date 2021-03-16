#include "mainscene.h"

MainScene::MainScene() : Scene() {

	backButton = new Button(Vector2(0, 0), "Back", "assets/kingkong.tga", std::bind(&MainScene::goBack, this), true);
	addChild(backButton);

	pencils = new EntityEmpty();
	pencils->addSpriteSheet("assets/frameTest.tga", 2, 1); //pencils.tga
	pencils->position = Vector2(200, 400);
	addChild(pencils);

	tileset = new EntityEmpty();
	tileset->addSpriteGrid("assets/tileset.tga", 8, 8, 4, 4);
	tileset->position = Vector2(800, 400);
	addChild(tileset);
}

MainScene::~MainScene() {

	removeChild(pencils);
	removeChild(tileset);
	removeChild(backButton);

	delete pencils;
	delete tileset;
	delete backButton;
}

void MainScene::update() {

	if (input()->getKeyDown(F)) {
		pencils->sprite->frame(pencils->sprite->frame() + 1);

		std::srand(std::time(0));
		for (size_t i = 0; i < tileset->spritebatch.size(); i++)
		{
			tileset->spritebatch[i]->frame(std::rand() % (tileset->spritebatch.size()));
		}
	}
}

void MainScene::goBack() {
	globals.currentScene = "menu";
}