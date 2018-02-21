#include "glutscene.hpp"
#include "basic_shapes.hpp"

using namespace std::placeholders;

glutscene::glutscene(std::pair<float, float> c, std::pair<int, int> r) :
	_canvas_size(c), _raster_size(r), 
    _current_width(3.0),
    _line_width(1.0),
    _part(color_tint(color_tint::colors::red), 
          transform(vector3(5.0, 5.0, 0.0), vector3(0.0, 0.0, 0.0), vector3(1.0, 1.0, 1.0)),
          vector3(0.1, 0.1, 0.0),
          robot_part::shape_type::rectangle)
{
    update_cursor();
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

    _part.draw();

    // basic_shapes::square();

    glutSwapBuffers();
}

void glutscene::keyboard(unsigned char key, int x, int y) {

}

void glutscene::mouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _mouse_pos.first = (float)x / _raster_size.first * _canvas_size.first;
        _mouse_pos.second = (float)(_raster_size.second - y) / _raster_size.second * _canvas_size.second;
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

	glutPostRedisplay();
}
