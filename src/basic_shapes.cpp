#include "basic_shapes.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cmath>

void basic_shapes::circle() {
	// Draw circle of radius 1
	glBegin(GL_TRIANGLE_FAN);
 
 	float radius = 0.5;
	for (int i=0; i < 100; i++) {
		float degInRad = (i * (360 / 100)) * (3.14159 / 180); // convert to radians. 
		glVertex2f(cos(degInRad) * radius, sin(degInRad) * radius);
	}

	glEnd();
}

void basic_shapes::square() {
	glBegin(GL_QUADS);
	glVertex2f(-0.5, -0.5);
	glVertex2f( 0.5, -0.5);
	glVertex2f( 0.5,  0.5);
	glVertex2f(-0.5,  0.5);
	glEnd();
}