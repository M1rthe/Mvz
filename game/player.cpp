#include "player.h"

Player::Player() : Entity() {
	speed = 70;
}

Player::~Player() {

}

void Player::update() {

	Vector2 newPos;

	if (input()->getKey(KeyCode::W)) {
		newPos.y -= speed * deltaTime;
	}
	if (input()->getKey(KeyCode::A)) {
		newPos.x -= speed * deltaTime;
	}
	if (input()->getKey(KeyCode::S)) {
		newPos.y += speed * deltaTime;
	}
	if (input()->getKey(KeyCode::D)) {
		newPos.x += speed * deltaTime;
	}

	//NORMALIZE
	float mag = sqrt((newPos.x * newPos.x) + (newPos.y * newPos.y));

	if (newPos.x != 0) {
		newPos.x /= mag;
	}
	if (newPos.y != 0) {
		newPos.y /= mag;
	}

	position += newPos;
}

