#pragma once
#include "figure_unit.h"
class figure_square : public figure_unit {
private:
	static const int quantity_of_point = 4;
	int array_x[quantity_of_point];
	int array_y[quantity_of_point];
	int array_x_move[quantity_of_point];
	int array_y_move[quantity_of_point];
	int array_x_crush[(quantity_of_point + 1)];
	int array_y_crush[(quantity_of_point + 1)];
	int delta_x = 15, delta_y = 15;
	void initialization_array(void);
	void coordinates_calculate(void);
	void crush_of_figure(void);
public:
	figure_square(int, int, unsigned int, bool, bool);
	figure_square(void);
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

