#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <mvz/vectorx.h>
#include <GL/glew.h>
#include <vector>
#include <mvz/color.h>

class Sprite {

public:
	Sprite(const std::string& imagepath, float u, float v, bool grayscale = false);
	virtual ~Sprite();

	GLuint texture() { return _texture; };
	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; };

	int width() { return _width; };
	int height() { return _height; };

	int frame(int f);
	int frame() { return _frame; };

	void generateBuffers();

	RGBAColor color;

	Vector2 spritePosition; //For spritebatch

	Vector2 uvoffset;
	Vector2 size;

private:
	GLuint loadTGA(const std::string& imagepath, bool grayscale = false);

	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;

	Vector2 uvdim;

	int _width = 0;
	int _height = 0;

	int _frame = 0;
};

#endif /* SPRITE_H */
