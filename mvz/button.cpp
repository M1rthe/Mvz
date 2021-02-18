#include <mvz/button.h>

Button::Button(Vector2 pos, std::string txt, std::string spriteName, std::function<void()> cbf) : Entity() {
	
	addSprite(spriteName, 1, 1);

	rect = Rectangle(pos.x, pos.y, sprite->width(), sprite->height());
	text = txt;
	callbackFunction = cbf;

	position = Vector2(rect.x + rect.width/2, rect.y + rect.height/2);
}

Button::~Button() {

}

void Button::update(float deltaTime) {

	if (input()->getMouseDown(0)) {
		if ((float)input()->getMouseX() > rect.x &&
			(float)input()->getMouseX() < rect.x + rect.width &&
			(float)input()->getMouseY() > rect.y &&
			(float)input()->getMouseY() < rect.y + rect.height) {

			callbackFunction();
		}
	}
}