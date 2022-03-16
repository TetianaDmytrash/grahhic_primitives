#pragma once
#include "figure.h"
#include "figure_check_mark.h"

class figure_unit:public figure {
	static const int quantity_of_object = 10;
	figure* arr_unit[quantity_of_object];
public:
	figure_unit(void);
	void figure_move(int, int);
	void figure_draw(void);
	void figure_position(int&, int&);
	void figure_position_for_track(int&, int&);
	void active_figure_paint(int);
	void active_figure_fill(int);
	void active_figure_clarity(int);
	void add_figure(figure*);
};

