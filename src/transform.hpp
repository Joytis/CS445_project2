#pragma once

#include <iostream>

#include "vector3.hpp"

class transform {
	vector3 _position; // applies to children. 
	vector3 _rotation; // applies to children
	vector3 _scale; // We don't have parents enforce scale. 

public:
	transform(vector3 pos = vector3(0.0, 0.0, 0.0), 
			  vector3 rot = vector3(0.0, 0.0, 0.0), 
			  vector3 scal = vector3(1.0, 1.0, 1.0));

	void apply_translate();
	void apply_rotation();
	void apply_scale();
	void apply_all();

	void apply_gl_matrix();

	friend std::ostream& operator<<(std::ostream& os, const transform& t);
};