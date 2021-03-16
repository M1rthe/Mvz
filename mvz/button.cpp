#include <mvz/button.h>

Button::Button(Vector2 pos, std::string txt, std::string spriteName, std::function<void()> cbf, bool autoTextSize) : Entity() {

	//SPRITE
	addSprite(spriteName);
	//POSITION
	pos.x += sprite->width() / 2;
	pos.y += sprite->height() / 2;
	position = pos;
	//TEXT
	text = new Text();
	addChild(text);
	text->setText(txt);
	text->color(RGBAColor(0, 0, 0));
	if (autoTextSize) {
		float s = (float)sprite->width() / (float)text->spritesWidth;
		text->scale = Vector2(s, s);
	}
	text->position.x = pos.x - sprite->width();
	text->position.y = pos.y - (sprite->height() / 2) - (text->spritesHeight * text->scale.y / 2);
	//CALLBACK
	callbackFunction = cbf;
}

Button::Button(Vector2 pos, std::vector<std::string> txt, std::string spriteName, std::function<void()> cbf, bool autoTextSize) : Entity() {

	//SPRITE
	addSprite(spriteName);
	//POSITION
	pos.x += sprite->width()/2;
	pos.y += sprite->height()/2;
	position = pos;
	//TEXT
	text = new Text();
	addChild(text);
	text->setTextLine(txt);
	text->color(RGBAColor(0, 0, 0));
	if (autoTextSize) {
		float s = (float)sprite->width() / (float)text->spritesWidth;
		text->scale = Vector2(s, s);
	}
	text->position.x = pos.x - sprite->width();
	text->position.y = pos.y - (sprite->height() / 2) - (text->spritesHeight * text->scale.y / 2);
	//CALLBACL
	callbackFunction = cbf;
}

Button::~Button() {

	removeChild(text);
	delete text;
}

void Button::update() {

	if (input()->getMouseDown(0)) {
		if ((float)input()->getMouseX() > position.x - (sprite->width() / 2) &&
			(float)input()->getMouseX() < position.x + (sprite->width() / 2) &&
			(float)input()->getMouseY() > position.y - (sprite->height() / 2) &&
			(float)input()->getMouseY() < position.y + (sprite->height() / 2)) {

			callbackFunction();
		}
	}
}