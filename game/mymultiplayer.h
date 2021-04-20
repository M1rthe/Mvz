#ifndef MYMULTIPLAYER_H
#define MYMULTIPLAYER_H

#include <mvz/client.h>
#include "mymultiplayer.h"
#include "mysingleplayer.h"

class MyMultiPlayer : public MySinglePlayer, public Client {

public:
	MyMultiPlayer();
	virtual ~MyMultiPlayer();
	virtual void update();

private:

};

#endif 

