#include <mvz/text.h>

Text::Text() : Entity() {

}

Text::~Text() {

}

void Text::update() {

}

void Text::setText(std::string txt) {

	addSpriteGrid("fonts/font.tga", 16, 8, 1, txt.size());
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
			//std::cout << txt[i] << " is too short by " << spacesToBeAdded << "\n";
			for (size_t j = 0; j < spacesToBeAdded; j++)
			{
				txt[i] += " ";
				//std::cout << "txt["<<i<<"] = "<<txt[i]<<".\n";
			}
		}
	}

	addSpriteGrid("fonts/font.tga", 16, 8, txt.size(), mostCharacters);
	for (size_t i = 0; i < txt.size(); i++) {
		for (size_t j = 0; j < mostCharacters; j++)
		{			
			//std::cout << i << ", " << j << " ("<<((txt.size()*j)+i)<<") = frame("<< txt[i][j] <<")\n";
			spritebatch[(txt.size() * j) + i]->frame((int)txt[i][j] - 32);
		}
	}
}

void Text::color(RGBAColor color) {
	std::cout << "Color: "<<color.toString()<<"\n";
}

void Text::color(HEXColor color) {
	this->color(Color::HEX2RGBA(color.hex));
}


