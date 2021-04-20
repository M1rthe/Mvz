#include "mymultiplayer.h"

MyMultiPlayer::MyMultiPlayer() : MySinglePlayer(), Client() {

}

MyMultiPlayer::~MyMultiPlayer() {
	std::cout << "DESTRUCTOR MyMultiPlayer" << std::endl;
}

void MyMultiPlayer::update() {
	MySinglePlayer::update();
}

