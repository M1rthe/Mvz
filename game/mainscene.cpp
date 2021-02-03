#include "mainscene.h"

MainScene::MainScene() : Scene() {

	pencils = new EntityEmpty();
	pencils->addSprite("assets/pencils.tga");
	pencils->position = Vector2(200, 200);
	addChild(pencils);
	/*
	kingkong = new Entity();
	kingkong->addSprite("assets/kingkong.tga");
	kingkong->position = Vector2(600, 200);
	addChild(kingkong);

	rgba = new Entity();
	rgba->addSprite("assets/rgba.tga");
	rgba->position = Vector2(400, 600);
	addChild(rgba);
	*/
}

MainScene::~MainScene() {
	//delete pencils;
	//delete kingkong;
	//delete rgba;
}

void MainScene::update(float deltaTime) {
	if (pencils->rotation.z > 360) { pencils->rotation.z = 0; }
	pencils->rotation.z += 1 * deltaTime;
}
