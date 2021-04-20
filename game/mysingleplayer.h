#ifndef MYSINGLEPLAYER_H
#define MYSINGLEPLAYER_H

#include <mvz/entity.h>

class MySinglePlayer : public Entity {

public:
	MySinglePlayer();
	virtual ~MySinglePlayer();
	virtual void update();

private:
	float speed;
};

#endif 

