#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "robot_part.hpp"
#include "basic_shapes.hpp"

robot_part::robot_part(color_tint tint, transform trans, vector3 joint, shape_type shape)
	: _tint(tint), _transform(trans), _joint(joint), _type(shape)
{
	std::cout << _transform << std::endl;
}

void robot_part::add_child(robot_part&& part) {

}

void robot_part::draw_joint() {
	// Now draw the joint!!
	glPushMatrix();
	glTranslatef(_joint.x, _joint.y, _joint.z);
	glColor3f(0.0, 0.0, 0.0); // draw outline as black
	glScalef(0.3, 0.3, 0.3); // Make tiny joints!
	basic_shapes::circle();
	_tint.apply_color();
	glScalef(0.7, 0.7, 0.7); // Make tiny joints!
	basic_shapes::circle();
	glPopMatrix();
	// Done with joint!!
}

void robot_part::draw() {
	glPushMatrix();

	_transform.apply_translate();
	_transform.apply_rotation();

	// NOTE(clark): I DON'T WANT SCALE TO BE AFFECTED BY PARENT FOR THIS PARTICULAR SIM!!
	glPushMatrix();
	_transform.apply_scale();

	// Make a cute little outline for the object.
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glScalef(1.05f, 1.05f, 1.05f);
	switch(_type) {
		case robot_part::shape_type::rectangle: 
			basic_shapes::square();
			break;
		case robot_part::shape_type::circle: 
			basic_shapes::circle();
			break;
	}
	glPopMatrix();
	// Outline done. 

	_tint.apply_color();
	switch(_type) {
		case robot_part::shape_type::rectangle: 
			basic_shapes::square();
			break;
		case robot_part::shape_type::circle: 
			basic_shapes::circle();
			break;
	}
	glPopMatrix();
	// Done drawing shape!
	draw_joint(); // DRAW THAT JOINT BOI

	// Draw children here. 

	glPopMatrix();	
}
