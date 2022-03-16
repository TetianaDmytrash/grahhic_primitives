#include "figure.h"

using namespace std;

static int my_number = 0;

void figure::figure_move(int x, int y) {}

void figure::figure_draw(void) {}

void figure::coordinates_calculate(void) {}

void figure::initialization_array(void){}

void figure::figure_position(int&, int&) {}

void figure::figure_position_for_track(int&, int&) {}

void figure::active_figure_paint(int) {}

void figure::active_figure_fill(int) {}

void figure::active_figure_clarity(int) {}

void figure::crush_of_figure(void) {}

void figure::range_min_and_max(void) {}

void figure::control_crush(bool) {}

void figure::add_figure(figure*) {}

void figure::return_to_start_position(void) {}

string figure::get_parameters(void){
	return "";
}

figure::figure(void) {
	figure_color[2] = 0xff & class_for_color::get_color(my_number);
	figure_color[1] = 0xff & (class_for_color::get_color(my_number) >> 8);
	figure_color[0] = 0xff & (class_for_color::get_color(my_number) >> 16);
	figure_clarity = true;
	need_of_calculation = true;
	figure_fill = true;
	figure_crush = false;
	my_number++;
	max_x = 0; max_y = 0; min_x = 0; min_y=0;
}

void figure::get_max_min(int* arr_max_min) {
	arr_max_min[0] = max_x;
	arr_max_min[1] = max_y;
	arr_max_min[2] = min_x;
	arr_max_min[3] = min_y;
}

unsigned int figure::collect_color(void) {
	unsigned int a;
	a = figure_color[0];
	a <<= 8;
	a += figure_color[1];
	a <<= 8;
	a += figure_color[2];
	//return (0xff & figure_color[0]) + ((0xff & figure_color [1])<<8)+((0xff & figure_color[2])<<16);
	return a;
}