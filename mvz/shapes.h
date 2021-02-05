#ifndef SHAPES_H
#define SHAPES_H

struct Circle {

	float x;
	float y;
	float radius;

	Circle(float x_ = 0, float y_ = 0, float r = 0) {
		this->x = x_;
		this->y = y_;
		this->radius = r;
	}
};

struct Rectangle {

	float x;
	float y;
	float width;
	float height;

	Rectangle(float x_ = 0, float y_ = 0, float w = 0, float h = 0) {
		this->x = x_;
		this->y = y_;
		this->width = w;
		this->height = h;
	}
};

#endif