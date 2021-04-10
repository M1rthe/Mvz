#include <mvz/button.h>

Button::Button(std::string txt, std::string spriteName, std::function<void()> cbf, bool autoTextSize) : Entity() {

	//SPRITE
	addSprite(spriteName);

	//TEXT
	text = new Text();
	addChild(text);
	text->setText(txt);
	this->autoTextSize = autoTextSize;

	//CALLBACK
	callbackFunction = cbf;

	//POSITION
	calculatePositions();
}

Button::Button(std::vector<std::string> txt, std::string spriteName, std::function<void()> cbf, bool autoTextSize) : Entity() {

	//SPRITE
	addSprite(spriteName);

	//TEXT
	text = new Text();
	addChild(text);
	text->setTextLine(txt);
	this->autoTextSize = autoTextSize;

	//CALLBACK
	callbackFunction = cbf;

	//POSITION
	calculatePositions();
}

Button::~Button() {

	removeChild(text);
	delete text;
}

void Button::update() {

	if (input()->getMouseDown(0)) {
		if ((float)input()->getMouseX() > position.x - (sprite->width() * scale.x / 2) &&
			(float)input()->getMouseX() < position.x + (sprite->width() * scale.x / 2) &&
			(float)input()->getMouseY() > position.y - (sprite->height() * scale.y / 2) &&
			(float)input()->getMouseY() < position.y + (sprite->height() * scale.y / 2)) {

			callbackFunction();
		}
	}
}

void Button::textColor(RGBAColor color) {
	for (size_t i = 0; i < text->spritebatch.size(); i++)
	{
		text->spritebatch[i]->color = color;
	}
}

void Button::textColor(HEXColor color) {
	for (size_t i = 0; i < text->spritebatch.size(); i++)
	{
		text->spritebatch[i]->color = Color::HEX2RGBA(color.hex);
	}
}

void Button::calculatePositions() {

	if (autoTextSize) {

		float sw = ((float)sprite->width() / (float)text->spritesWidth) * 0.9f;
		float sh = ((float)sprite->height() / (float)text->spritesHeight) * 0.9f;

		if (sw < sh) {
			text->scale = Vector2(sw, sw * (scale.x / scale.y));
		}
		else {
			text->scale = Vector2(sh, sh);
		}
	}

	text->position.x = -(text->spritesWidth * text->scale.x / 2);
	text->position.y = -(text->spritesHeight * text->scale.y / 2);
}