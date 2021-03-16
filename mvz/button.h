#ifndef BUTTON_H
#define BUTTON_H

#include <mvz/entity.h>
#include <mvz/shapes.h>
#include <mvz/text.h>
#include <functional>
#include <mvz/color.h>

class Button : public Entity {

public:
	Button(Vector2 pos, std::string txt, std::string spriteName, std::function<void()> cbf, bool autoTextSize);
	Button(Vector2 pos, std::vector<std::string> txt, std::string spriteName, std::function<void()> cbf, bool autoTextSize);
	~Button();
	virtual void update();

private:
	Text* text;
	std::function<void()> callbackFunction = NULL;
};

#endif
