#ifndef TEXT_H
#define TEXT_H

#include <mvz/entity.h>
#include <mvz/color.h>

class Text : public Entity {

public:
	Text();
	virtual ~Text();
	virtual void update();

	void setText(std::string txt);
	void setTextLine(std::vector<std::string> txt);
};

#endif