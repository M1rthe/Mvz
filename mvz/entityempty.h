#ifndef ENTITYEMPTY_H
#define ENTITYEMPTY_H

#include <mvz/entity.h>

class EntityEmpty : public Entity {

public:
	EntityEmpty();
	~EntityEmpty();
	virtual void update(float deltaTime);
};

#endif