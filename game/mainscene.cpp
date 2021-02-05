#include "mainscene.h"

MainScene::MainScene() : Scene() {

	pencils = new EntityEmpty();
	pencils->addSprite("assets/pencils.tga");
	pencils->position = Vector2(200, 200);
	addChild(pencils);
}

MainScene::~MainScene() {
	delete pencils;
}

void MainScene::update(float deltaTime) {

	if (pencils->rotation.z > 6) { pencils->rotation.z = 0; }
	
	pencils->rotation.z += 1 * deltaTime;

	if (input()->getKeyDown(Space)) {
		globals.currentScene = "menu";
	}
}
