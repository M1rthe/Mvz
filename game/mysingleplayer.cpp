#include "mysingleplayer.h"

MySinglePlayer::MySinglePlayer() : Entity() {
	speed = 100;
}

MySinglePlayer::~MySinglePlayer() {
	std::cout << "DESTRUCTOR MySinglePlayer" << std::endl;
}

void MySinglePlayer::update() {

	Vector2 newPos;

	if (input()->getKey(KeyCode::W)) {
		newPos.y -= 1;
	}
	if (input()->getKey(KeyCode::A)) {
		newPos.x -= 1;
	}
	if (input()->getKey(KeyCode::S)) {
		newPos.y += 1;
	}
	if (input()->getKey(KeyCode::D)) {
		newPos.x += 1;
	}

	//NORMALIZE
	float mag = sqrt((newPos.x * newPos.x) + (newPos.y * newPos.y));

	if (newPos.x != 0) {
		newPos.x /= mag;
	}
	if (newPos.y != 0) {
		newPos.y /= mag;
	}

	position += newPos * speed * deltaTime;
}

