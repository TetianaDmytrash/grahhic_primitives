#pragma once
#include "figure_unit.h"
#include <math.h>

class figure_circle : public figure_unit {
private:
	static const int quantity_of_point = 55;
	float array_x[quantity_of_point];
	float array_y[quantity_of_point];
	float array_x_move[quantity_of_point];
	float array_y_move[quantity_of_point];
	float array_x_crush[quantity_of_point];
	float array_y_crush[quantity_of_point];
	float radius = 10;
	void coordinates_calculate(void);
	void initialization_array(void);
	void crush_of_figure(void);
public:
	figure_circle(int, int, unsigned int, bool, bool);
	figure_circle(void);
	void figure_draw(void);
	void figure_move(int, int);
	void figure_position(int&, int&);
	void figure_position_for_track(int&, int&);
	void active_figure_paint(int);
	void active_figure_fill(int);
	void active_figure_clarity(int);
	string get_parameters(void);
	void return_to_start_position(void);
	void control_crush(bool);
};

