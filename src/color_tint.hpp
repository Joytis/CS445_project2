#pragma once

#include "color.hpp"

class color_tint {
private:
	s_color _color;

public:
	enum class colors {
		red, 
		orange, 
		yellow, 
		green, 
		blue,
		purple
	};

	color_tint();
	color_tint(float r, float g, float b);
	color_tint(colors c);

	void apply_color();
};