#include "figure_triangle.h"

void figure_triangle::coordinates_calculate(void) {
	array_x_move[1] = array_x[1] = array_x[0] + delta_x;
	array_x_move[2] = array_x[2] = array_x[0] - delta_x;
	array_y_move[1] = array_y[1] = array_y[0] + delta_y;
	array_y_move[2] = array_y[2] = array_y[1];
}

figure_triangle::figure_triangle(int x, int y, unsigned int my_color, bool clar, bool paint) {
	figure_color[2] = 0xff & my_color;
	figure_color[1] = 0xff & (my_color >> 8);
	figure_color[0] = 0xff & (my_color >> 16);
	figure_clarity = clar;
	figure_fill = paint;
	initialization_array();
	kind_of_figure = figure::triangle;
	array_x_move[0] = array_x[0] = x;
	array_y_move[0] = array_y[0] = y;
	need_of_calculation = true;
}

figure_triangle::figure_triangle(void) {
	initialization_array();
	kind_of_figure = figure::triangle;
	int delta_x_calculation = delta_x + 1, delta_y_calculation = delta_y + 1;
	array_x_move[0] = array_x[0] = delta_x_calculation + rand() % (180 - delta_x_calculation);//height-20
	array_y_move[0] = array_y[0] = delta_y_calculation + rand() % (120 - delta_y_calculation);//width-20
}

void figure_triangle::figure_draw(void) {
	if (need_of_calculation) {
		coordinates_calculate();
		class_for_range::range_max_and_min_int(array_x_move, &max_x, &min_x, quantity_of_point);
		class_for_range::range_max_and_min_int(array_y_move, &max_y, &min_y, quantity_of_point);
		need_of_calculation = false;
	}

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!figure_clarity) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
	}
	else {
		if (!figure_crush) {
			glLineWidth(3);//толщина линии
			glColor3ub(figure_color[0], figure_color[1], figure_color[2]);
			if (figure_fill) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < quantity_of_point; i++) {
				glVertex2d(array_x_move[i], array_y_move[i]);
			}
			glEnd();
		}
		else {
			glLineWidth(3);//толщина линии
			glColor3ub(figure_color_crush[0], figure_color_crush[1], figure_color_crush[2]);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			if (figure_fill) {
				glBegin(GL_TRIANGLE_FAN);
				for (int i = 0; i < (quantity_of_point +1); i++) {
					glVertex2d(array_x_crush[i], array_y_crush[i]);
				}
				glEnd();
			}
			else {
				glBegin(GL_LINE_LOOP);
				for (int i = 1; i < (quantity_of_point + 1); i++) {
					glVertex2d(array_x_crush[i], array_y_crush[i]);
				}
				glEnd();
			}
		}
	}
	if (!figure_clarity) {
		glDisable(GL_BLEND);
	}
}

void figure_triangle::figure_move(int x, int y) {
	class_for_range::move_max_min_int(array_x_move, &max_x, &min_x, quantity_of_point, x);
	class_for_range::move_max_min_int(array_y_move, &max_y, &min_y, quantity_of_point, y);
}

void figure_triangle::crush_of_figure(void) {
	array_x_crush[0] = array_x_move[0];
	array_y_crush[0] = array_y_move[0];
	array_x_crush[1] = array_x_move[1];
	array_y_crush[1] = array_y_move[1];
	array_x_crush[2] = array_x_move[0];
	array_y_crush[2] = array_y_move[1];
	array_x_crush[3] = array_x_move[0]-delta_x/2;
	array_y_crush[3] = array_y_move[0]+delta_y/2;
}

void figure_triangle::control_crush(bool flag) {
	if (flag) {
		figure_crush = true;
		crush_of_figure();
	}
	else {
		figure_crush = false;
	}
}

void figure_triangle::initialization_array(void) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x[i] = 0;
		array_y[i] = 0;
		array_x_move[i] = 0;
		array_y_move[i] = 0;
	}
}

void figure_triangle::figure_position(int& x, int& y) {
	for (int i = 0; i < quantity_of_point; i++) {
		x += array_x_move[i];
		y += array_y_move[i];
	}
	x = x / quantity_of_point;
	y = y / quantity_of_point;
}

void figure_triangle::figure_position_for_track(int& x, int& y) {
	x = array_x_move[1];
	y = array_y_move[1];
}

void figure_triangle::active_figure_paint(int num_color) {
	figure_color[2] = 0xff & class_for_color::get_selected_color(num_color);
	figure_color[1] = 0xff & (class_for_color::get_selected_color(num_color) >> 8);
	figure_color[0] = 0xff & (class_for_color::get_selected_color(num_color) >> 16);
}

void figure_triangle::active_figure_fill(int switch_fill) {
	if (switch_fill == 1) {
		figure_fill = false;
	}
	else {
		figure_fill = true;
	}
}

void figure_triangle::active_figure_clarity(int switch_view) {
	if (switch_view == 3) {
		figure_clarity = false;
	}
	else if (switch_view == 2) {
		figure_clarity = true;
	}
}

string figure_triangle::get_parameters(void) {//отдать
	string str = "";
	str += to_string(kind_of_figure) + " ";
	str += to_string(array_x_move[0]) + " ";
	str += to_string(array_y_move[0]) + " ";
	str += to_string(figure::collect_color()) + " ";
	str += figure_clarity ? "1 " : "0 ";
	str += figure_fill ? "1 " : "0 ";
	//kind_of_figure_t;
	//int x, y;
	//int figure_color[3];
	//bool figure_clarity;
	//bool figure_fill;
	return str;
}

void figure_triangle::return_to_start_position(void) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x_move[i] = array_x[i];
		array_y_move[i] = array_y[i];
	}
}