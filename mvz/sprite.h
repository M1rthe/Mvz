#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <GL/glew.h>

class Sprite {

public:
	Sprite(const std::string& imagepath);
	virtual ~Sprite();

	GLuint texture() { return _texture; };
	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; };

	int width() { return _width; };
	int height() { return _height; };

private:
	GLuint loadTGA(const std::string& imagepath);

	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;

	int _width;
	int _height;
};

#endif /* SPRITE_H */
