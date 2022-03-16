#pragma once
#include "figure.h"
class figure_point : public figure {
private:
	static const int quantity_of_point = 7;
	int array_x[quantity_of_point];
	int array_y[quantity_of_point];
	bool max_quantity_of_point;
public:
	//так как этой фигурой буду пользоваться только я, ей не нужен конструктор с пользовательским вводом
	figure_point(void);
	void figure_draw(void);
	void figure_move(int, int);
	void initialization_array(void);
};

