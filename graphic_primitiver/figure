#pragma once
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include "class_for_color.h"
#include "class_for_range.h"

using namespace std;

class figure {
public:
	static const int general_quantity_of_figure = 10;
	enum kind_of_figure_t {circle = 1, line, star, triangle, square,new_fig , point, check_mark };
	kind_of_figure_t kind_of_figure;
	virtual void figure_draw(void);
	virtual void figure_move(int x, int y);
	virtual void figure_position(int&, int&);
	virtual void figure_position_for_track(int&, int&);
	figure(void);
	virtual void active_figure_paint(int);
	virtual void active_figure_fill(int);
	virtual void active_figure_clarity(int);
	virtual void control_crush(bool);
	virtual void add_figure(figure*);
	virtual void return_to_start_position(void);
	virtual string get_parameters(void);
	void get_max_min(int*);
protected:
	int max_x, max_y, min_x, min_y;
	bool figure_clarity;
	bool need_of_calculation;
	bool figure_fill;
	bool figure_crush;
	int figure_color[3];
	int figure_color_select[3] = { 0,0,0 };
	int figure_color_crush[3] = { 255,126,0 };
	virtual void crush_of_figure(void);
	virtual void coordinates_calculate(void);
	virtual void initialization_array(void);
	unsigned int collect_color(void);

private:
	void range_min_and_max(void);
};
