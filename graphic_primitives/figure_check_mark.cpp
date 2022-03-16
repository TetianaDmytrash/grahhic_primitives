#include "figure_check_mark.h"

using namespace std;

void figure_check_mark::coordinates_calculate(void) {
	/*int delta_x_calculation = delta_x + 1, delta_y_calculation = delta_y + 1;
	array_x_move[1] = array_x[1] = delta_x_calculation + rand() % (200 - delta_x_calculation);//height
	array_y_move[1] = array_y[1] = delta_y_calculation + rand() % (140 - delta_y_calculation);//width
	array_x_move[0] = array_x[0] = array_x[1] - delta_x;
	array_x_move[2] = array_x[2] = array_x[1] + delta_x;
	array_y_move[0] = array_y[0] = array_y[1] - delta_y;
	array_y_move[2] = array_y[2] = array_y[0];*/
}

void figure_check_mark::initialization_array(void) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x[i] = 0;
		array_y[i] = 0;
		array_x_move[i] = 0;
		array_y_move[i] = 0;
	}
}

figure_check_mark::figure_check_mark(void) {
	initialization_array();
	kind_of_figure = check_mark;
}

void figure_check_mark::figure_draw(void) {
	/*if (need_of_calculation) {//false
		coordinates_calculate();
		need_of_calculation = false;
	}
	*/
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(6);
	glColor3ub(figure_color_select[0], figure_color_select[1], figure_color_select[2]);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < quantity_of_point; i++) {
		glVertex2d(array_x_move[i], array_y_move[i]);
	}


	glEnd();

	//glutSwapBuffers();
}

void figure_check_mark::figure_move(int x, int y) {
	array_x_move[1] = array_x[1] = x;
	array_y_move[1] = array_y[1] = y;
	array_x_move[0] = array_x[0] = array_x[1] - delta_x;
	array_x_move[2] = array_x[2] = array_x[1] + delta_x;
	array_y_move[0] = array_y[0] = array_y[1] - delta_y;
	array_y_move[2] = array_y[2] = array_y[0];

}

void figure_check_mark::figure_position_for_track(int& x, int& y) {
	x = array_x_move[1];
	y = array_y_move[1];
}