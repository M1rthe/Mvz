#ifndef COLOR_H_
#define COLOR_H_

#include <algorithm>
#include <cmath>
#include <math.h> 
#include <map>

struct RGBAColor
{
	uint8_t r = 255;
	uint8_t g = 255;
	uint8_t b = 255;
	uint8_t a = 255;

	RGBAColor() {
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	RGBAColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	RGBAColor(uint8_t red, uint8_t green, uint8_t blue) {
		r = red;
		g = green;
		b = blue;
		a = 255;
	}

	RGBAColor(uint32_t color) {
		r = color >> 24 & 0xFF;
		g = color >> 16 & 0xFF;
		b = color >> 8 & 0xFF;
		a = color & 0xFF;
	}

	uint32_t asInt() {
		uint32_t color = (r << 24) + (g << 16) + (b << 8) + (a);
		return color;
	}

	inline bool operator==(const RGBAColor& rhs) {
		return (r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);
	}

	inline bool operator!=(const RGBAColor& rhs) {
		return !(*this == rhs);
	}
};

struct HEXColor {
	std::string hex = "FFFFF";

	HEXColor() {
		hex = "FFFFF";
	}

	HEXColor(std::string h) {
		hex = h;
	}
};

struct Color {

	static HEXColor RGBA2HEX(RGBAColor rgba) {

		std::string hex = "";
		char values[] = {'0', '1', '2', '3', '4',  '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

		hex += values[(int)std::floor(rgba.r/16)];
		hex += values[rgba.r%16];
		hex += values[(int)std::floor(rgba.g / 16)];
		hex += values[rgba.g % 16];
		hex += values[(int)std::floor(rgba.b / 16)];
		hex += values[rgba.b % 16];

		std::cout << "from rgb("<< unsigned(rgba.r)<<", "<< unsigned(rgba.g)<<", "<< unsigned(rgba.b)<<") to #"<<hex<<"\n";

		return HEXColor(hex);
	}

	static RGBAColor HEX2RGBA(std::string hex) {

		std::map<char, int> values = { {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15} };

		uint8_t r = (values.find(hex.at(0))->second * 16) + values.find(hex.at(1))->second;
		uint8_t g = (values.find(hex.at(2))->second * 16) + values.find(hex.at(3))->second;
		uint8_t b = (values.find(hex.at(4))->second * 16) + values.find(hex.at(5))->second;

		std::cout << "from hex #"<<hex<<" to rgb("<< unsigned(r) <<", "<<unsigned(g)<<", "<<unsigned(b)<<")\n";

		return RGBAColor(r, g, b, 255);
	}
};

#define BLACK		RGBAColor(0,   0,   0) 
#define GRAY		RGBAColor(127, 127, 127) 
#define RED			RGBAColor(255, 0,   0) 
#define ORANGE		RGBAColor(255, 127, 0) 
#define YELLOW		RGBAColor(255, 255, 0) 
#define GREEN		RGBAColor(0,   255, 0) 
#define LIME		RGBAColor(116, 191, 50)
#define CYAN		RGBAColor(0,   255, 255) 
#define DARKBLUE	RGBAColor(0,   0,   255) 
#define BLUE		RGBAColor(10, 163, 245)
#define MAGENTA		RGBAColor(255, 0,   255) 
#define PURPLE		RGBAColor(162, 55,  184)
#define PINK		RGBAColor(252, 157, 220)  
#define WHITE		RGBAColor(255, 255, 255) 
#define BROWN		RGBAColor(101, 67,  33)

#endif
