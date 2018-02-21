#pragma once

struct s_color {
	float r;
	float g;
	float b;

	s_color() : r(0.0), g(0.0), b(0.0) {}
	s_color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
};