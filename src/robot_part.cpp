#include <iostream>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "robot_part.hpp"
#include "basic_shapes.hpp"

robot_part::robot_part(color_tint tint, transform trans, vector3 joint, shape_type shape)
	: _tint(tint), _transform(trans), _joint(joint), _type(shape), 
	  _fsm(robot_part::states::neutral), _dot_scale(0.3)
{
	// define state transitions. . 
	_fsm.add_transition(states::neutral, states::mouseover, triggers::lmouse_over);

	_fsm.add_transition(states::mouseover, states::neutral, triggers::lmouse_not_over);
	_fsm.add_transition(states::mouseover, states::selected, triggers::lmouse_down);

	_fsm.add_transition(states::selected, states::neutral, triggers::lmouse_up);
}

void robot_part::add_child(robot_part&& part) {
	_children.push_back(std::forward<robot_part>(part)); // forward to vector pushback. 
}

// Send the state machine a trigger. 
void robot_part::send_trigger(robot_part::triggers trig) {
	_fsm.set_trigger(trig);

	for(auto& child : _children)
		child.send_trigger(trig); // propegate to children. 
} 

// update with mouse position.
void robot_part::update(float x, float y) {
	
	float mouse_distance = x - _previous_pos.first;

	// Use the matrix stack to determine whether or not we're intersecting with a point. 
	glPushMatrix();

	// Apply basic transform, then sit at center of joint. 
	apply_basic_translations();

	glPushMatrix();
	_transform.apply_scale();
	glTranslatef(_joint.x, _joint.y, _joint.z);
	_transform.apply_inverse_scale();

	// CHECK IF POINT IS WITHIN JOINT RANGE.  =================
	GLfloat model[16]; 
	glGetFloatv(GL_MODELVIEW_MATRIX, model); 
	GLfloat point[4];
	// Multiply point by modelview matrix. 
	point[0] = model[12 + 0]; // Transform position is what I want. 
	point[1] = model[12 + 1]; // Transform position is what I want. 
	point[2] = model[12 + 2]; // Transform position is what I want. 
	point[3] = model[12 + 3]; // Transform position is what I want. 

	float distance = sqrt(pow(point[0] - x, 2) + pow(point[1] - y, 2)); // pythagorean
	if(distance <= (_dot_scale / 2)) 
		_fsm.set_trigger(triggers::lmouse_over);
	else 
		_fsm.set_trigger(triggers::lmouse_not_over);
	glPopMatrix();

	_fsm.update();


	// Define sate behavior. 
	switch(_fsm.get_current_state()) {
		case states::neutral: {
			// COlor black. 
			_outline_color.r = 0.0;
			_outline_color.g = 0.0;
			_outline_color.b = 0.0;
		}break;
		case states::mouseover: {
			// color red
			_outline_color.r = 0.8;
			_outline_color.g = 0.0;
			_outline_color.b = 0.0;
		}break;
		case states::selected: {
			// Apply a rotation to the rotation transform!
			float rot_add = mouse_distance * -30.0;

			vector3 rot = _transform.get_rotation();
			rot.z += rot_add;
			_transform.set_rotation(rot);

			// color green
			_outline_color.r = 0.0;
			_outline_color.g = 0.8;
			_outline_color.b = 0.0;
		}break;
	}

	// Update all the children, too!
	for(auto& child : _children) 
		child.update(x, y);

	_previous_pos.first = x; 	
	_previous_pos.second = y; 

	glPopMatrix();

}

// Draw joints seperately so they're on top of the shapes. 
void robot_part::draw_joints() {

	glPushMatrix();
	apply_basic_translations();
	// Now draw the joint!!
	glPushMatrix();
	_transform.apply_scale();
	glTranslatef(_joint.x, _joint.y, _joint.z);
	_transform.apply_inverse_scale();
	glColor3f(_outline_color.r, _outline_color.g, _outline_color.b);
	glScalef(_dot_scale, _dot_scale, _dot_scale); // Make tiny joints!
	basic_shapes::circle();
	_tint.apply_color();
	glScalef(0.7, 0.7, 0.7); // Make tiny joints!
	basic_shapes::circle();
	glPopMatrix();
	// Done with joint!!

	for(auto& child : _children) 
		child.draw_joints(); // draw children :Draw

	glPopMatrix();
}

void robot_part::apply_basic_translations() {
	_transform.apply_translate();
	_transform.apply_scale();
	glTranslatef(_joint.x, _joint.y, _joint.z);
	_transform.apply_inverse_scale();
	_transform.apply_rotation();
	_transform.apply_scale();
	glTranslatef(-_joint.x, -_joint.y, -_joint.z);
	_transform.apply_inverse_scale();
}


// Draw the shapes seperately so they're under the joints. 
void robot_part::draw_shapes() {
	glPushMatrix();

	apply_basic_translations();

	// NOTE(clark): I DON'T WANT SCALE TO BE AFFECTED BY PARENT FOR THIS PARTICULAR SIM!!
	glPushMatrix();
	_transform.apply_scale(); // Do our scale. 
	glColor3f(_outline_color.r, _outline_color.g, _outline_color.b);
	switch(_type) {
		case robot_part::shape_type::rectangle: 
			basic_shapes::square();
			break;
		case robot_part::shape_type::circle: 
			basic_shapes::circle();
			break;
	}
	// Outline done. 

	// Draw the actual shape. 
	glPushMatrix();
	glScalef(0.95, 0.95, 1.0); // Then make it a little smaller. 
	_tint.apply_color();
	switch(_type) {
		case robot_part::shape_type::rectangle: 
			basic_shapes::square();
			break;
		case robot_part::shape_type::circle: 
			basic_shapes::circle();
			break;
	}
	glPopMatrix(); // ... Then get rid of scale
	glPopMatrix(); // ... for both the square and the outline. 
	// Done drawing shape!
	
	// Draw children here. 
	for(auto& child : _children) 
		child.draw_shapes();

	glPopMatrix();	
}
