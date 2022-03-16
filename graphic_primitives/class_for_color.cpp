#include "class_for_color.h"

using namespace std;

enum type_of_color_t {
	light_green = 4325120, pink = 16711889, lilac = 11796637, dark_blue = 18101,
	turquoise = 65535, dark_green = 39458, light_blue = 4430591,
	purple = 7864477, yellow = 16776960, swampy = 10131968
};

static int how_many = 0;

static int opportunity_color[10] = { light_green, pink, lilac, dark_blue,
						  turquoise, dark_green,  light_blue,
						  purple, yellow, swampy };

int class_for_color::get_color(int index) {
	return (int)opportunity_color[index % 10];
}

int class_for_color::get_selected_color(int index) {//для перерисовки по выбранному цвету
	return (int)opportunity_color[index];
}

void class_for_color::out_all(void)
{
	for (int i = 0; i < sizeof(opportunity_color) / sizeof(type_of_color_t); i++) {
		cout << i << " = " << opportunity_color[i] << " ";
	}
	cout << endl;
}