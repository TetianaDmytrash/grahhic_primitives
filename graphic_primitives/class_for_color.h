#pragma once
#include <iostream>

class class_for_color
{
protected:
	int type_of_color;

public:
	void out_all(void);
	static int get_color(int);
	static int get_selected_color(int);
};