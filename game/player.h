#ifndef PLAYER_H
#define PLAYER_H

#include <mvz/entity.h>

class Player : public Entity {

public:
	Player();
	virtual ~Player();
	virtual void update();

private:
	float speed;
};

#endif 

