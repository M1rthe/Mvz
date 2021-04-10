#ifndef BUTTON_H
#define BUTTON_H

#include <mvz/entity.h>
#include <mvz/shapes.h>
#include <mvz/text.h>
#include <functional>
#include <mvz/color.h>

class Button : public Entity {

public:
	Button(std::string txt, std::string spriteName, std::function<void()> cbf, bool autoTextSize);
	Button(std::vector<std::string> txt, std::string spriteName, std::function<void()> cbf, bool autoTextSize);
	virtual ~Button();
	virtual void update();

	void textColor(RGBAColor color);
	void textColor(HEXColor color);

	void calculatePositions();

private:
	Text* text;
	std::function<void()> callbackFunction = NULL;
	bool autoTextSize;
};

#endif
