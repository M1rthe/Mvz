#ifndef BUTTON_H
#define BUTTON_H

#include <mvz/entity.h>
#include <mvz/shapes.h>
#include <functional>

class Button : public Entity {

public:
	Button(Vector2 rect, std::string txt, std::string spriteName, std::function<void()> cbf);
	~Button();
	virtual void update();

private:
	Rectangle rect;
	std::string text = "";
	std::function<void()> callbackFunction = NULL;
};

#endif
