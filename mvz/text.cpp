#include <mvz/text.h>

Text::Text() : Entity() {

}

Text::~Text() {

}

void Text::update() {

}

void Text::setText(std::string txt) {

	addSpriteGrid("fonts/font.tga", 16, 8, 1, txt.size(), true);
	for (size_t i = 0; i < txt.size(); i++) {
		spritebatch[i]->frame((int)txt[i] - 32);
	}
}

void Text::setTextLine(std::vector<std::string> txt) {

	int mostCharacters = 0;

	for (size_t i = 0; i < txt.size(); i++) {
		if (txt[i].size() > mostCharacters) {
			mostCharacters = txt[i].size();
		}
	}

	for (size_t i = 0; i < txt.size(); i++) {

		if (txt[i].size() < mostCharacters) {
			int spacesToBeAdded = mostCharacters - txt[i].size();
			for (size_t j = 0; j < spacesToBeAdded; j++)
			{
				txt[i] += " ";
			}
		}
	}

	addSpriteGrid("fonts/font.tga", 16, 8, txt.size(), mostCharacters, true);
	for (size_t i = 0; i < txt.size(); i++) {

		for (size_t j = 0; j < mostCharacters; j++)
		{			
			spritebatch[(txt.size() * j) + i]->frame((int)txt[i][j] - 32);
		}
	}
}

