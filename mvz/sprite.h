#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <mvz/vectorx.h>
#include <GL/glew.h>
#include <vector>

class Sprite {

public:
	Sprite(const std::string& imagepath, float u, float v);
	virtual ~Sprite();

	GLuint texture() { return _texture; };
	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; };

	int width() { return _width; };
	int height() { return _height; };

	int frame(int f);
	int frame() { return _frame; };

	void generateBuffers();

	Vector2 spritePosition; //For spritebatch

	Vector2 uvoffset;
	Vector2 size;

private:
	GLuint loadTGA(const std::string& imagepath);

	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;

	Vector2 uvdim;

	int _width;
	int _height;

	int _frame = 0;
};

#endif /* SPRITE_H */
