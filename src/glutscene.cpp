#include "glutscene.hpp"
#include "basic_shapes.hpp"

using namespace std::placeholders;

glutscene::glutscene(std::pair<float, float> c, std::pair<int, int> r) :
	_canvas_size(c), _raster_size(r), 
    _current_width(3.0),
    _line_width(1.0),
    // Create the first part for the robot. 
    _part(color_tint(color_tint::colors::red), 
          transform(vector3(5.0, 4.0, 0.0), vector3(0.0, 0.0, 0.0), vector3(1.5, 0.7, 1.0)),
          vector3(0.0, -0.5, 0.0),
          robot_part::shape_type::rectangle)
{
    update_cursor();

    // NOTE(clark): This all kind of gross, but I didn't feel like defining a file parser for all this...
    // Create all the other robot parts here. 
    //================ Rightmost Leg. ========================
    robot_part right_thigh(color_tint(color_tint::colors::orange), // Color dawg. 
                          transform(vector3(0.5, -.85, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(0.55, 1.0, 1.0)), // scale
                          vector3(0.0, 0.5, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

    robot_part right_calf(color_tint(color_tint::colors::yellow), // Color dawg. 
                          transform(vector3(0.0, -1.0, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(0.55, 1.0, 1.0)), // scale
                          vector3(0.0, 0.5, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

    robot_part right_foot(color_tint(color_tint::colors::green), // Color dawg. 
                          transform(vector3(0.25, -0.75, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(0.8, 0.5, 1.0)), // scale
                          vector3(-0.25, 0.5, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

    //================ Leftmost leg ========================
    robot_part left_thigh(color_tint(color_tint::colors::orange), // Color dawg. 
                          transform(vector3(-0.5, -.85, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(0.55, 1.0, 1.0)), // scale
                          vector3(0.0, 0.5, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

    robot_part left_calf(color_tint(color_tint::colors::yellow), // Color dawg. 
                          transform(vector3(0.0, -1.0, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(0.55, 1.0, 1.0)), // scale
                          vector3(0.0, 0.5, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

    robot_part left_foot(color_tint(color_tint::colors::green), // Color dawg. 
                          transform(vector3(-0.25, -0.75, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(0.8, 0.5, 1.0)), // scale
                          vector3(0.25, 0.5, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

    //================ Torso ========================
    robot_part belly(color_tint(color_tint::colors::orange), // Color dawg. 
                          transform(vector3(0.0, .85, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(1.0, 1.0, 1.0)), // scale
                          vector3(0.0, -0.5, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

    robot_part chest(color_tint(color_tint::colors::yellow), // Color dawg. 
                          transform(vector3(0.0, 1.0, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(1.5, 1.0, 1.0)), // scale
                          vector3(0.0, -0.5, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

    //================ Right arm ========================
    robot_part right_shoulder(color_tint(color_tint::colors::green), // Color dawg. 
                          transform(vector3(1.25, 0.25, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(1.0, 0.4, 1.0)), // scale
                          vector3(-0.5, 0.0, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

     robot_part right_arm(color_tint(color_tint::colors::blue), // Color dawg. 
                          transform(vector3(1.0, 0.0, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(1.0, 0.4, 1.0)), // scale
                          vector3(-0.5, 0.0, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

      robot_part right_hand(color_tint(color_tint::colors::purple), // Color dawg. 
                          transform(vector3(0.8, 0.0, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(0.7, 0.7, 1.0)), // scale
                          vector3(-0.5, 0.0, 0.0), // joint offset
                          robot_part::shape_type::circle); // Shape. 

    //================ Left arm ========================
    robot_part left_shoulder(color_tint(color_tint::colors::green), // Color dawg. 
                          transform(vector3(-1.25, 0.25, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(1.0, 0.4, 1.0)), // scale
                          vector3(0.5, 0.0, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

    robot_part left_arm(color_tint(color_tint::colors::blue), // Color dawg. 
                          transform(vector3(-1.0, 0.0, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(1.0, 0.4, 1.0)), // scale
                          vector3(0.5, 0.0, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape. 

    robot_part left_hand(color_tint(color_tint::colors::purple), // Color dawg. 
                          transform(vector3(-0.8, 0.0, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(0.7, 0.7, 1.0)), // scale
                          vector3(0.5, 0.0, 0.0), // joint offset
                          robot_part::shape_type::circle); // Shape.  

    //================ Head ========================
    robot_part neck(color_tint(color_tint::colors::green), // Color dawg. 
                          transform(vector3(0.0, 0.7, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(0.5, 0.4, 1.0)), // scale
                          vector3(0.0, -0.5, 0.0), // joint offset
                          robot_part::shape_type::rectangle); // Shape.  

    robot_part head(color_tint(color_tint::colors::blue), // Color dawg. 
                          transform(vector3(0.0, 0.9, 0.0),  // position
                                    vector3(0.0, 0.0, 0.0),  // rotation 
                                    vector3(1.5, 1.5, 1.0)), // scale
                          vector3(0.0, -0.5, 0.0), // joint offset
                          robot_part::shape_type::circle); // Shape.  



    // Staple the whole robot together. 
    // right leg. 
    right_calf.add_child(std::move(right_foot));
    right_thigh.add_child(std::move(right_calf)); 

    // left leg
    left_calf.add_child(std::move(left_foot));
    left_thigh.add_child(std::move(left_calf));     

    // Right arm
    right_arm.add_child(std::move(right_hand));
    right_shoulder.add_child(std::move(right_arm));

    // Left arm
    left_arm.add_child(std::move(left_hand));
    left_shoulder.add_child(std::move(left_arm));

    // Head
    neck.add_child(std::move(head));

    // Midsection
    chest.add_child(std::move(right_shoulder));
    chest.add_child(std::move(left_shoulder));
    chest.add_child(std::move(neck));
    belly.add_child(std::move(chest));

    // Main node. 
    _part.add_child(std::move(right_thigh)); 
    _part.add_child(std::move(left_thigh)); 
    _part.add_child(std::move(belly)); 

}

void glutscene::reshape(int w, int h) {
	_raster_size.first = w;
    _raster_size.second = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, _canvas_size.first, 0.0, _canvas_size.second);
    glViewport(0, 0, _raster_size.first, _raster_size.second);
    
    glutPostRedisplay();
}

void glutscene::display() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // glColor3f(1.0, 0.0, 0.0);
    // glTranslatef(5.0, 5.0, 0.0);
    // glRotatef(0.0, 0.0, 0.0, 1.0);
    // glScalef(2.0, 2.0, 1.0);

    _part.draw_shapes();
    _part.draw_joints();

    // basic_shapes::square();

    glutSwapBuffers();
}

void glutscene::keyboard(unsigned char key, int x, int y) {

}

void glutscene::mouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _mouse_pos.first = (float)x / _raster_size.first * _canvas_size.first;
        _mouse_pos.second = (float)(_raster_size.second - y) / _raster_size.second * _canvas_size.second;
        _part.send_trigger(robot_part::triggers::lmouse_down);
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        _mouse_pos.first = (float)x / _raster_size.first * _canvas_size.first;
        _mouse_pos.second = (float)(_raster_size.second - y) / _raster_size.second * _canvas_size.second;
        _part.send_trigger(robot_part::triggers::lmouse_up);
    }

}

void glutscene::motion(int x, int y) {
	
	// mouse events are handled by OS, eventually. When using mouse in the raster window,
	//  it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
	_mouse_pos.first = (float)x / _raster_size.first * _canvas_size.first;
    _mouse_pos.second = (float)(_raster_size.second - y) / _raster_size.second * _canvas_size.second;

    glutPostRedisplay();
}

// Forward the callback to openGL
void glutscene::createMenu(void (*menu)(int)) {

}

void glutscene::update_cursor() {
    // just make a new one. 

}

void glutscene::menu(int value) {
    
}

void glutscene::cull_point_if_needed() {

}

void glutscene::create_new_primative() {

}

void glutscene::idle() {

    _part.update(_mouse_pos.first, _mouse_pos.second);

	glutPostRedisplay();
}
