#pragma once

#include <vector>
#include <unordered_map>

#include "color_tint.hpp"
#include "transform.hpp"
#include "fsm/fsm.hpp"

class robot_part {
public:
	enum class shape_type {
		rectangle,
		circle
	};

	enum class triggers {
		lmouse_over = (1 << 0),
		lmouse_not_over = (1 << 1),
		lmouse_down = (1 << 2),
		lmouse_up = (1 << 3)
	};
private:

	enum class states {
		neutral,
		mouseover,
		selected
	};

	color_tint _tint;
	transform _transform;
	vector3 _joint;
	shape_type _type;
	fsm::finite_state_system<states, triggers> _fsm; // state machine. 
	float _dot_scale;

	s_color _outline_color;
	std::pair<float, float> _previous_pos;
	std::vector<robot_part> _children;

	void apply_basic_translations();


public:
	robot_part(color_tint tint, transform trans, vector3 joint, shape_type shape);
	void add_child(robot_part&& part);

	void draw_shapes();
	void draw_joints();

	void send_trigger(triggers trig);
	void update(float x, float y);
};

ENABLE_BITMASK_OPERATORS(robot_part::triggers)
