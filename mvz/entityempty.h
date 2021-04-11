#ifndef ENTITYEMPTY_H
#define ENTITYEMPTY_H

#include <mvz/entity.h>

class EntityEmpty : public Entity {

public:
	EntityEmpty();
	virtual ~EntityEmpty();
	virtual void update();
};

#endif