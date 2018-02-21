#pragma once

#include <vector>
#include <unordered_map>

#include "color_tint.hpp"
#include "transform.hpp"

class robot_part {
public:
	enum class shape_type {
		rectangle,
		circle
	};

private:

	color_tint _tint;
	transform _transform;
	vector3 _joint;
	shape_type _type;

	std::vector<robot_part> _children;

	void draw_joint();

public:
	robot_part(color_tint tint, transform trans, vector3 joint, shape_type shape);
	void add_child(robot_part&& part);
	void draw();
};