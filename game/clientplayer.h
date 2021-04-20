#ifndef PLAYER_H
#define PLAYER_H

#include <mvz/entity.h>
#include <mvz/client.h>

class ClientPlayer : public Entity {

public:
	ClientPlayer();
	ClientPlayer(SOCKET sock);
	virtual ~ClientPlayer();
	virtual void update();

	SOCKET socket;

private:
	
};

#endif 

