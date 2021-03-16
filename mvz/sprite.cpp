#include <iostream>
#include <cstdio>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include <mvz/sprite.h>

Sprite::Sprite(const std::string& imagepath, float u, float v) {

	_width = 0;
	_height = 0;

	color = RGBAColor(255, 255, 255, 255);

	spritePosition = Vector2(0.0, 0.0);

	uvdim = Vector2(u, v);
	uvoffset = Vector2(0.0, 0.0);
	size = Vector2(0.0, 0.0);

	_texture = loadTGA(imagepath);

	generateBuffers();
}

Sprite::~Sprite() {
	glDeleteBuffers(1, &_vertexbuffer);
	glDeleteBuffers(1, &_uvbuffer);
	glDeleteTextures(1, &_texture); // texture created in loadTGA() with glGenTextures()

	//delete pixelBufferData;
}

GLuint Sprite::loadTGA(const std::string& imagepath) {

	FILE *file;
	unsigned char type[4];
	unsigned char info[6];

	file = fopen(imagepath.c_str(), "rb");

	if (!file) {
		std::cout << "error: unable to open file" << std::endl;
		return 0;
	}

	if (!fread (&type, sizeof (char), 3, file)) return 0;
	fseek (file, 12, SEEK_SET);
	if (!fread (&info, sizeof (char), 6, file)) return 0;

	//image type needs to be 2 (color) or 3 (grayscale)
	if (type[1] != 0 || (type[2] != 2 && type[2] != 3))
	{
		std::cout << "error: image type neither color or grayscale" << std::endl;
		fclose(file);
		return 0;
	}

	unsigned char* data;
	unsigned char bitdepth;

	_width = info[0] + info[1] * 256;
	_height = info[2] + info[3] * 256;
	bitdepth = info[4] / 8;

	if (bitdepth != 1 && bitdepth != 3 && bitdepth != 4) {
		std::cout << "bytecount not 1, 3 or 4" << std::endl;
		fclose(file);
		return 0;
	}

	// Check if the image's width and height is a power of 2. No biggie, we can handle it.
	if ((_width & (_width - 1)) != 0) {
		std::cout << "warning: " << imagepath << " width is not a power of 2" << std::endl;
	}
	if ((_height & (_height - 1)) != 0) {
		std::cout << "warning: " << imagepath << " height is not a power of 2" << std::endl;
	}
	if (_width != _height) {
		std::cout << "warning: " << imagepath << " is not square" << std::endl;
	}

	unsigned int imagesize = _width * _height * bitdepth;

	//Create a buffer
	data = new unsigned char [imagesize];

	//Read the actual data from the file into the buffer
	if (!fread(data, 1, imagesize, file)) return 0;

	//Everything is in memory now, close the file
	fclose(file);

	//Create one OpenGL texture
	//Be sure to also delete it from where you called this with glDeleteTextures()
	GLuint textureID;
	glGenTextures(1, &textureID);

	//"Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Filter the Texture
	unsigned char filter = 1;
	switch (filter) {
		case 0:
			// No filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
		case 1:
			// Linear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		case 2:
			// Bilinear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		case 3:
			// Trilinear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		default:
			// No filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
	}

	//Wrapping
	//GL_REPEAT, GL_MIRRORED_REPEAT or GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//Handle transparency and grayscale and give the image to OpenGL
	switch (bitdepth) {
		case 4:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
			break;
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
			break;
		case 1:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, _width, _height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
			break;
		default:
			std::cout << "error: bitdepth not 4, 3, or 1" << std::endl;
			break;
	}

	//OpenGL has now copied the data. Free our own version
	delete [] data;

	//Return the ID of the texture we just created
	return textureID;
}

void Sprite::generateBuffers() {

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	float uvwidth = uvdim.x;
	float uvheight = uvdim.y;
	float pivotx = 0.5f;
	float pivoty = 0.5f;

	if (size.x == 0) { size.x = _width * uvdim.x; }
	if (size.y == 0) { size.y = _height * uvdim.y; }

	// first triangle
	vertices.push_back(glm::vec3(-size.x * pivotx, -size.y * pivoty, 0.0f));
	vertices.push_back(glm::vec3(-size.x * pivotx, size.y - (size.y * pivoty), 0.0f));
	vertices.push_back(glm::vec3(size.x - (size.x * pivotx), size.y - (size.y * pivoty), 0.0f));
	// second triangle
	vertices.push_back(glm::vec3(size.x - (size.x * pivotx), size.y - (size.y * pivoty), 0.0f));
	vertices.push_back(glm::vec3(size.x - (size.x * pivotx), -size.y * pivoty, 0.0f));
	vertices.push_back(glm::vec3(-size.x * pivotx, -size.y * pivoty, 0.0f));

	// UV coordinates for each vertex.
	// uvs for first triangle
	uvs.push_back(glm::vec2(0.0f, uvheight));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(uvwidth, 0.0f));
	// uvs for second triangle
	uvs.push_back(glm::vec2(uvwidth, 0.0f));
	uvs.push_back(glm::vec2(uvwidth, uvheight));
	uvs.push_back(glm::vec2(0.0f, uvheight));

	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

int Sprite::frame(int f) {

	int w = 1.0f / uvdim.x;
	int h = 1.0f / uvdim.y;

	if (f >= w * h) {
		_frame = 0;
		uvoffset.x = 0;
		uvoffset.y = 0;
		return _frame;
	}

	int ypos = f / w;
	int xpos = f % w;

	uvoffset.x = xpos * uvdim.x;
	uvoffset.y = ypos * uvdim.y;

	_frame = f;

	return _frame;
}

void Sprite::grayscaleAsAlphaMap() {

	/*
	int amountOfPixels = size.x * size.y;

	if (pixelBufferData != nullptr) {
		delete pixelBufferData;
		pixelBufferData = nullptr;
	}

	pixelBufferData = new unsigned char[amountOfPixels];

	std::cout << "amountOfPixels: "<<amountOfPixels<<"("<< _width <<" * "<< _height <<")\n";

	int counter = 0;
	for (int i = 0; i < amountOfPixels; i++) {

		pixelBufferData[counter + 0] = 255;
		pixelBufferData[counter + 1] = 255;
		pixelBufferData[counter + 2] = 255;
		pixelBufferData[counter + 3] = pixelBufferData[(counter + 3) / 4];
		
		counter += 4;
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelBufferData);
	*/
}