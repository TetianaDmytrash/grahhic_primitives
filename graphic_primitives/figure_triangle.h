#pragma once
#include "figure_unit.h"

class figure_triangle : public figure_unit {
private:
	static const int quantity_of_point = 3;
	void coordinates_calculate(void);
	void crush_of_figure(void);
	void initialization_array(void);
	int array_x[quantity_of_point];
	int array_y[quantity_of_point];
	int array_x_move[quantity_of_point];
	int array_y_move[quantity_of_point];
	int array_x_crush[(quantity_of_point+1)];
	int array_y_crush[(quantity_of_point+1)];
	int delta_x = 10, delta_y = 20;
public:
	figure_triangle(int, int, unsigned int, bool, bool);
	figure_triangle(void);
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

