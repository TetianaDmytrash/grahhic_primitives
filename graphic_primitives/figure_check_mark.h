#pragma once
#include "figure.h"
class figure_check_mark : public figure {
private:
	static const int quantity_of_point = 3;
	void coordinates_calculate(void);
	int array_x[quantity_of_point];
	int array_y[quantity_of_point];
	int array_x_move[quantity_of_point];
	int array_y_move[quantity_of_point];
	int delta_x = 3, delta_y = 6;
public:
	//так как этой фигурой буду пользоваться только я, ей не нужен конструктор с пользовательским вводом
	figure_check_mark(void);
	void figure_draw(void);
	void figure_move(int, int);
	void initialization_array(void);
	void figure_position_for_track(int&, int&);
};

