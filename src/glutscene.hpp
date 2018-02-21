#pragma once

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <utility>
#include <functional>
#include <vector>

#include "color.hpp"
#include "robot_part.hpp"

class glutscene {

private:

	std::pair<float, float> _canvas_size;
	std::pair<int, int> _raster_size;
	std::pair<float, float> _mouse_pos;
	s_color _current_color;

	float _current_width;
	float _line_width;
	
	robot_part _part;

public:
	glutscene(std::pair<float, float> c, std::pair<int, int> r);

	void cull_point_if_needed();

	void createMenu(void (*menu)(int));
	void create_new_primative();
	void update_cursor();

	void reshape(int w, int h);
	void display(void);
	void keyboard(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void menu(int value);
	void idle();
};