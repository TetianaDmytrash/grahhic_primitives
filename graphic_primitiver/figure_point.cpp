#include "figure_point.h"

#include "figure_check_mark.h"

using namespace std;

void figure_point::initialization_array(void) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x[i] = 0;
		array_y[i] = 0;
	}
}

figure_point::figure_point(void) {
	initialization_array();
	max_quantity_of_point = false;
	//kind_of_figure = point;
}

void figure_point::figure_draw(void) {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(6);
	glColor3ub(figure_color_select[0], figure_color_select[1], figure_color_select[2]);
	for (int i = 0; i < quantity_of_point; i++) {
		if ((array_x[i] != 0) && (array_y[i] != 0)) {
			glBegin(GL_POINTS);
			glVertex2d(array_x[i], array_y[i]);
			glEnd();
		}
	}


	

	//glutSwapBuffers();
}

void figure_point::figure_move(int x, int y) {
	for (int i = 0; i < quantity_of_point; i++) {
		if ((array_x[i] == 0) && (array_y[i] == 0)) {
			array_x[i] = x;
			array_y[i] = y;
			if (i == (quantity_of_point - 1)) {
				initialization_array();
			}
			break;
		}
	}
}