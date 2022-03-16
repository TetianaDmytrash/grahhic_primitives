#pragma once
#include "figure_unit.h"
#include <math.h>

class figure_star : public figure_unit {
private:
	static const int quantity_of_point = 12;
	void coordinates_calculate(void);
	float array_x[quantity_of_point];
	float array_y[quantity_of_point];
	float array_x_move[quantity_of_point];
	float array_y_move[quantity_of_point];
	float array_x_crush[(quantity_of_point-1)];
	float array_y_crush[(quantity_of_point-1)];
	float radius = 10;
	float radius_small = 4;
	void initialization_array(void);
	void crush_of_figure(void);
public:
	figure_star(int, int, unsigned int, bool, bool);
	figure_star(void);
	void figure_draw(void);
	void figure_move(int, int);
	void figure_position(int&, int&);
	void figure_position_for_track(int&, int&);
	void active_figure_paint(int);
	void active_figure_fill(int);
	void active_figure_clarity(int);
	void control_crush(bool);
	string get_parameters(void);
	void return_to_start_position(void);
};

