#include "clientplayer.h"

ClientPlayer::ClientPlayer() : Entity() {
	socket = INVALID_SOCKET;
}

ClientPlayer::ClientPlayer(SOCKET _socket) : Entity() {
	socket = _socket;
}

ClientPlayer::~ClientPlayer() {

}

void ClientPlayer::update() {

}

