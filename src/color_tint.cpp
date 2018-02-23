#include "color_tint.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif



color_tint::color_tint() : _color(s_color(0.0, 0.0, 0.0)) {}
color_tint::color_tint(float r, float g, float b) : _color(s_color(r, g, b)) {}

color_tint::color_tint(color_tint::colors c) {
	
	switch(c) {
		case color_tint::colors::red: 
			_color = s_color(1.0, 0.0, 0.0);
			break;

		case color_tint::colors::orange: 
			_color = s_color(1.0, 0.64, 0.0);
			break;

		case color_tint::colors::yellow: 
			_color = s_color(1.0, 0.95, 0.0);
			break;

		case color_tint::colors::green: 
			_color = s_color(0.0, 1.0, 0.0);
			break;

		case color_tint::colors::blue: 
			_color = s_color(0.0, 0.0, 1.0);
			break;

		case color_tint::colors::purple: 
			_color = s_color(0.56, 0.0, 0.8);
			break;

	}
}

void color_tint::apply_color() {
	glColor3f(_color.r, _color.g, _color.b);
}