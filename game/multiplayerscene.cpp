#include "multiplayerscene.h"

MultiplayerScene::MultiplayerScene() : Scene() {
	backButton = new Button("Back", "assets/button.tga", std::bind(&MultiplayerScene::goBack, this), true);
	backButton->scale = Vector2(3, 3);
	backButton->position = Vector2(-(backButton->sprite->width() * backButton->scale.x / 2) + globals.windowWidth, -(backButton->sprite->height() * backButton->scale.y / 2) + globals.windowHeight);
	addChild(backButton);
	backButton->sprite->color = BLUE;
	backButton->textColor(WHITE);

	player = new Player();
	player->addSprite("assets/player.tga", true);
	player->sprite->color = PINK;
	player->scale = Vector2(2, 2);
	player->position = Vector2(200, 400);
	addChild(player);
}

MultiplayerScene::~MultiplayerScene() {

}

void MultiplayerScene::update() {

}

void MultiplayerScene::goBack() {
	globals.currentScene = "multiplayerMenu";
}

