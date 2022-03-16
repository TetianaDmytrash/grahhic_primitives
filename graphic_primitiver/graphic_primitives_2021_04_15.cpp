// graphic_primitives_2021_04_15.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <GL/freeglut.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include "figure.h"
#include "figure_circle.h"
#include "figure_star.h"
#include "figure_triangle.h"
#include "figure_line.h"
#include "figure_square.h"
#include "class_for_color.h"
#include "figure_check_mark.h"
#include "figure_point.h"
#include "figure_unit.h"

using namespace std;

const int width_Win = 1000;
const int height_Win = 700;

int selector_figure_active_now = 0;//для мерцания и галочки активная фигура
int counter_for_move = 0, max_quantity_move = 7;//для движения
bool check_figure_unit = true;//для создания нового агрегата
bool test_of_meet_figure = false;//для проверки пересечения
char* file_name;//для файла

int number_first_empty = 0;
figure* arr_fig[figure::general_quantity_of_figure];
figure_check_mark general_check_mark;
figure_point general_point;

//для библиотеки
void reshape(int width, int height);
void general_draw(void);
void keyboard(unsigned char key, int x, int y);
void special_key(int s_key, int m, int z);

//для таймеров
void move_without_track(int value);
void move_with_track(int value);

//
void search_number_first_empty(void);
int search_number_first_filled(int start);
void start_filled_figure(void);
void move_with_special_key(int x, int y);//для движения стрелками
bool test_of_meet(void);//для столкновения фигур
void description_general_menu(void);//для общего меню

//для меню
int type_of_figure, color_of_figure, fill_of_figure, clarity_of_figure, call_of_figure;
bool menuFlag;
void type_of_figure_func(int value);
void color_of_figure_func(int value);
void fill_of_figure_func(int value);
void clarity_of_figure_func(int value);
void call_of_figure_func(int value) {};
void create_figure_main_menu(void);
enum { select_circle = 1, select_line, select_star, select_triangle, select_square, select_new};
enum {
	select_light_green = 0, select_pink, select_lilac, select_dark_blue, select_turquoise,
	select_dark_green, select_light_blue, select_purple, select_yellow, select_swampy
};
enum { select_fill, select_empty, select_view, select_hidden };

int main(int argc, char* argv[])
{
	cout << " You should click on the left mouse button to start working " << endl;
	cout << " F1 - call general description " << endl;
	for (int i = 0; i < figure::general_quantity_of_figure; i++) {
		arr_fig[i] = NULL;
	}
	// #1: Инициализация и создание окна GLUT
	glutInit(&argc, argv);//инициализация GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);//режим отображения информации
												 //GLUT_DOUBLE - вывод в окно с использованием 2 буферов
												 //GLUT_RGBA - RGB + прозрачность
	glutInitWindowPosition(50, 50);//отношение относительно верхнего левого угла экрана
	glutCreateWindow("HI!");//создание окна с заголовком
	glutInitWindowSize(height_Win, width_Win);//размеры окна
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glutAttachMenu(GLUT_LEFT_BUTTON);//для разблокировки клавиатуры
	int counter_for_read = 0;
	bool availability_of_file = true;
	if (argc == 2) {
		unsigned int buff[6];
		file_name = argv[1];
		bool end_exit = false;
		ifstream fin;
		fin.open(file_name);
		if (!fin) {
			cout << "Can`t find this file : " << file_name;
			availability_of_file = false;
		}
		else {
			string str;
			int i = 0;
			while (!end_exit) {
				for (int j = 0; j < 6; j++) {
					fin >> buff[j];
					if (fin.eof()) {
						//cout << " I did my best. " << endl;
						end_exit = true;
						break;
					}
					counter_for_read++;
				}
				if (end_exit) {
					break;
				}
				switch (buff[0]) {
				case select_circle:
					arr_fig[i] = new figure_circle(buff[1], buff[2], buff[3], buff[4], buff[5]);
					break;
				case select_line:
					arr_fig[i] = new figure_line(buff[1], buff[2], buff[3], buff[4], buff[5]);
					break;
				case select_star:
					arr_fig[i] = new figure_star(buff[1], buff[2], buff[3], buff[4], buff[5]);
					break;
				case select_triangle:
					arr_fig[i] = new figure_triangle(buff[1], buff[2], buff[3], buff[4], buff[5]);
					break;
				case select_square:
					arr_fig[i] = new figure_square(buff[1], buff[2], buff[3], buff[4], buff[5]);
					break;
				default:
					cout << " OBLOM " << endl;
					break;
				}
				if (++i >= figure::general_quantity_of_figure)
					break;
			}
		}
	}
	if ((counter_for_read == 0) ||(!availability_of_file)) {//если нет файла
		arr_fig[0] = new figure_triangle;
		arr_fig[1] = new figure_star;
		arr_fig[2] = new figure_square;
		arr_fig[3] = new figure_circle;
	}



	start_filled_figure();
	// #2: Регистрация функций-обработчиков событий
	glutReshapeFunc(reshape);

	glutDisplayFunc(general_draw);// для рисования/перерисовки содержимого окна


	glutSpecialFunc(special_key);
	glutKeyboardFunc(keyboard);

	// инициализация меню
	create_figure_main_menu();

	// #3: Запуск основного цикла GLUT
	glutMainLoop();
	return 1;
}

void reshape(int width, int height)
{

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	// Следующие действия производятся с матрицей проекции
	glLoadIdentity();//обнуление матрицы?
	glutReshapeWindow(width_Win, height_Win);
	gluOrtho2D(0, 200, 140, 0);
	glViewport(0, 0, width_Win, height_Win);
	glMatrixMode(GL_MODELVIEW);
	// Следующие действия производятся с матрицей модели

}

void general_draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//буфера цвета и глубины
	for (int i = 0; i < figure::general_quantity_of_figure; i++) {
		if (arr_fig[i] != NULL) {
			arr_fig[i]->figure_draw();
		}
	}
	general_check_mark.figure_draw();
	general_point.figure_draw();
	glFlush();
	glutSwapBuffers();
}

void move_without_track(int value) {
	int x = 0, y = 0;
	if (counter_for_move != max_quantity_move) {
		x = -5 + rand() % 5;
		y = -2 + rand() % 5;
		test_of_meet_figure = test_of_meet();
		arr_fig[selector_figure_active_now]->figure_move(x, y);
		int x_p = 0, y_p = 0;
		arr_fig[selector_figure_active_now]->figure_position(x_p, y_p);
		x += x_p;
		y += y_p;
		general_check_mark.figure_move(x, y);

		glutPostRedisplay();
		glutTimerFunc(1000, move_without_track, 0);
		counter_for_move++;
	}

}

void move_with_track(int value) {
	int x = 0, y = 0;
	if (counter_for_move != max_quantity_move) {
		x = -5 + rand() % 5;
		y = -2 + rand() % 5;
		test_of_meet_figure = test_of_meet();
		arr_fig[selector_figure_active_now]->figure_move(x, y);
		int x_p = 0, y_p = 0;
		int x_p_for_track = 0, y_p_for_track = 0;
		arr_fig[selector_figure_active_now]->figure_position(x_p, y_p);
		arr_fig[selector_figure_active_now]->figure_position_for_track(x_p_for_track, y_p_for_track);
		x += x_p;
		y += y_p;
		general_check_mark.figure_move(x, y);
		general_point.figure_move(x_p_for_track, y_p_for_track);

		glutPostRedisplay();
		glutTimerFunc(1000, move_with_track, 0);
		counter_for_move++;
	}
}

void move_with_special_key(int x, int y) {
	test_of_meet_figure = test_of_meet();
	arr_fig[selector_figure_active_now]->figure_move(x, y);
	int x_p = 0, y_p = 0;
	arr_fig[selector_figure_active_now]->figure_position(x_p, y_p);
	x += x_p;
	y += y_p;
	general_check_mark.figure_move(x, y);
	glutPostRedisplay();
}

#define max_x_act arr_max_min_for_activ_figure[0]
#define max_y_act arr_max_min_for_activ_figure[1]
#define min_x_act arr_max_min_for_activ_figure[2]
#define min_y_act arr_max_min_for_activ_figure[3]
#define max_x_pas arr_max_min_for_passiv_figure[0]
#define max_y_pas arr_max_min_for_passiv_figure[1]
#define min_x_pas arr_max_min_for_passiv_figure[2]
#define min_y_pas arr_max_min_for_passiv_figure[3]

bool test_of_meet(void) {
	int arr_max_min_for_activ_figure[4];
	int arr_max_min_for_passiv_figure[4];
	arr_fig[selector_figure_active_now]->get_max_min(arr_max_min_for_activ_figure);
	for (int i = 0; i < figure::general_quantity_of_figure; i++) {
		if ((arr_fig[i] != NULL) && (i != selector_figure_active_now)) {
			arr_fig[i]->get_max_min(arr_max_min_for_passiv_figure);
			if ((min_x_act < max_x_pas) && (max_y_act > min_y_pas) &&
				(max_x_act > min_x_pas) && (min_y_act < max_y_pas)) {
				arr_fig[selector_figure_active_now]->control_crush(true);
				arr_fig[i]->control_crush(true);
				//cout << " bingo 1 " << endl;
				return true;
			}
			else if ((min_x_act < max_x_pas) && (min_y_act < max_y_pas) &&
				(max_x_act > min_x_pas) && (max_y_act > min_y_pas)) {
				arr_fig[selector_figure_active_now]->control_crush(true);
				arr_fig[i]->control_crush(true);
				//cout << " bingo 2 " << endl;
				return true;
			}
			else if ((max_x_act > min_x_pas) && (max_y_act > min_y_pas) &&
				(min_x_act < max_x_pas) && (min_y_act < max_y_pas)) {
				arr_fig[selector_figure_active_now]->control_crush(true);
				arr_fig[i]->control_crush(true);
				//cout << " bingo 3 " << endl;
				return true;
			}
			else if ((max_x_act > min_x_pas) && (min_y_act < max_y_pas) &&
				(min_x_act < max_x_pas) && (max_y_act > min_y_pas)) {
				arr_fig[selector_figure_active_now]->control_crush(true);
				arr_fig[i]->control_crush(true);
				//cout << " bingo 4 " << endl;
			}
			else {
				arr_fig[selector_figure_active_now]->control_crush(false);
				arr_fig[i]->control_crush(false);
			}
		}
	}
	return true;
}

void check_on_unit(void) {
	if (check_figure_unit) {
		search_number_first_empty();
		arr_fig[number_first_empty] = new figure_unit;
		arr_fig[number_first_empty]->add_figure(arr_fig[selector_figure_active_now]);
		arr_fig[selector_figure_active_now] = NULL;
		selector_figure_active_now = number_first_empty;
		check_figure_unit = false;
	}
	else {
		arr_fig[number_first_empty]->add_figure(arr_fig[selector_figure_active_now]);
		arr_fig[selector_figure_active_now] = NULL;
		selector_figure_active_now = number_first_empty;
	}

}

void description_general_menu(void) {
	cout << " F1 - call general description " << endl;
	cout << " F2 - move active object without track " << endl;
	cout << " F3 - move active object with track " << endl;
	cout << " F4 - save object in file " << endl;
	cout << " F5 - start to do unit " << endl;
	cout << " F6 - end to do unit " << endl;
	cout << " F7 - quantity objects " << endl;
	cout << " F8 - delete object " << endl;
	cout << " F9 - return on start position " << endl;
	cout << " Use the arrows to move the object " << endl;
	cout << " Pressing 'space' makes the next object active " << endl;
	cout << " Esc allows you to exit the program " << endl;
	cout << " Calling up the menu - clicking on the right mouse button " << endl;
	cout << " Exit the menu - clicking on the right or on the left mouse button " << endl;
	cout << " Create an object - the first menu item " << endl;
	cout << " Change color - the second menu item " << endl;
	cout << " Change fill - the third menu item " << endl;
	cout << " Change clarity - the fourth menu item " << endl;
}

int count_quantity = 0;//общее количество объектов
void special_key(int s_key, int m, int z) {
	int x = 0, y = 0;
	int x_p_f = 0, y_p_f = 0;
	switch (s_key) {
	case GLUT_KEY_F1:
		//вывод всех возможностей в консоль
		description_general_menu();
		break;
	case GLUT_KEY_F2:
		counter_for_move = 0;
		glutTimerFunc(1000, move_without_track, 0);
		break;
	case GLUT_KEY_F3:
		counter_for_move = 0;
		glutTimerFunc(1000, move_with_track, 0);
		break;
	case GLUT_KEY_F4:
		if (file_name != NULL) {
			ofstream fout(file_name);
			for (int i = 0; i < figure::general_quantity_of_figure; i++) {
				if (arr_fig[i] != NULL) {
					fout << arr_fig[i]->get_parameters() << endl;
				}
			}
			fout.flush();
			fout.close();
		}
		cout << " changes saved " << endl;
		break;
	case GLUT_KEY_F5:
		check_on_unit();
		break;
	case GLUT_KEY_F6:
		check_figure_unit = true;
		break;
	case GLUT_KEY_F7:
		count_quantity = 0;
		for (int i = 0; i < figure::general_quantity_of_figure; i++) {
			if (arr_fig[i] != NULL) {
				count_quantity++;
			}
		}
		cout << " quantity objects - " << count_quantity << endl;
		break;
	case GLUT_KEY_F8:
		arr_fig[selector_figure_active_now] = NULL;
		glutPostRedisplay();
		break;
	case GLUT_KEY_F9:
		arr_fig[selector_figure_active_now]->return_to_start_position();
		arr_fig[selector_figure_active_now]->figure_position(x_p_f, y_p_f);
		general_check_mark.figure_move(x_p_f, y_p_f);
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		x = -2; y = 0;
		move_with_special_key(x, y);
		break;
	case GLUT_KEY_RIGHT:
		x = 2; y = 0;
		move_with_special_key(x, y);
		break;
	case GLUT_KEY_UP:
		x = 0; y = -2;
		move_with_special_key(x, y);
		break;
	case GLUT_KEY_DOWN:
		x = 0; y = 2;
		move_with_special_key(x, y);
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(0); // 27 - код клавиши Esc
	if (key == ' ') {
		selector_figure_active_now = search_number_first_filled(selector_figure_active_now);
		if (selector_figure_active_now >= 0) {
			int x_p = 0, y_p = 0;
			arr_fig[selector_figure_active_now]->figure_position(x_p, y_p);//выбранный
			general_check_mark.figure_move(x_p, y_p);
		}
		glutPostRedisplay();
	}
}

void search_number_first_empty(void) {
	for (int i = 0; i < figure::general_quantity_of_figure; i++) {
		if (arr_fig[i] == NULL) {
			number_first_empty = i;
			return;
		}
	}
	number_first_empty = -1;
}

int search_number_first_filled(int start) {

	for (int i = 0; i < figure::general_quantity_of_figure; i++) {
		start++;
		if (start >= figure::general_quantity_of_figure) {
			start = 0;
		}
		if (arr_fig[start] != NULL) {
			return start;
		}
	}
	return -1;
}

void start_filled_figure(void) {
	for (int i = 0; i < figure::general_quantity_of_figure; i++) {
		if (arr_fig[i] != NULL) {
			selector_figure_active_now = i;
		}
	}
	if (selector_figure_active_now >= 0) {
		int x_p = 0, y_p = 0;
		arr_fig[selector_figure_active_now]->figure_position(x_p, y_p);//выбранный
		general_check_mark.figure_move(x_p, y_p);
	}
	glutPostRedisplay();
}

//menu
void create_figure_main_menu(void) {
	type_of_figure = glutCreateMenu(type_of_figure_func);
	glutAddMenuEntry("  circle  ", select_circle);
	glutAddMenuEntry("   line   ", select_line);
	glutAddMenuEntry("   star   ", select_star);
	glutAddMenuEntry(" triangle ", select_triangle);
	glutAddMenuEntry("  square  ", select_square);
	glutAddMenuEntry("   *new*  ", select_new);
	color_of_figure = glutCreateMenu(color_of_figure_func);
	glutAddMenuEntry("  light_green  ", select_light_green);
	glutAddMenuEntry("      pink     ", select_pink);
	glutAddMenuEntry("     lilac     ", select_lilac);
	glutAddMenuEntry("   dark_blue   ", select_dark_blue);
	glutAddMenuEntry("   turquoise   ", select_turquoise);
	glutAddMenuEntry("   dark_green  ", select_dark_green);
	glutAddMenuEntry("   light_blue  ", select_light_blue);
	glutAddMenuEntry("     purple    ", select_purple);
	glutAddMenuEntry("     yellow    ", select_yellow);
	glutAddMenuEntry("     swampy    ", select_swampy);
	fill_of_figure = glutCreateMenu(fill_of_figure_func);
	glutAddMenuEntry("    fill     ", select_fill);
	glutAddMenuEntry("    empty    ", select_empty);
	clarity_of_figure = glutCreateMenu(clarity_of_figure_func);
	glutAddMenuEntry("    view     ", select_view);
	glutAddMenuEntry("   hidden    ", select_hidden);
	call_of_figure = glutCreateMenu(call_of_figure_func);
	glutAddSubMenu("  create object  ", type_of_figure);
	glutAddSubMenu("      color      ", color_of_figure);
	glutAddSubMenu("       fill      ", fill_of_figure);
	glutAddSubMenu("     clarity     ", clarity_of_figure);
	// прикрепить меню к правой кнопке
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void type_of_figure_func(int value) {
	search_number_first_empty();
	if (number_first_empty >= 0) {
		switch (value) {
		case select_circle:
			arr_fig[number_first_empty] = new figure_circle;
			break;
		case select_line:
			arr_fig[number_first_empty] = new figure_line;
			break;
		case select_star:
			arr_fig[number_first_empty] = new figure_star;
			break;
		case select_triangle:
			arr_fig[number_first_empty] = new figure_triangle;
			break;
		case select_square:
			arr_fig[number_first_empty] = new figure_square;
			break;
		case select_new:
			cout << " Sorry, I haven't been invented yet " << endl;
			//arr_fig[number_first_empty] = new figure_*new*;
			break;
		default:
			cout << " I don`t know this kind of figures " << endl;
			break;
		}
		glFlush();
		glutPostRedisplay();
	}
	else {
		cout << " game over :) " << endl;
	}
}

void color_of_figure_func(int value) {
	switch (value) {
	case select_light_green:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_light_green);
		break;
	case select_pink:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_pink);
		break;
	case select_lilac:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_lilac);
		break;
	case select_dark_blue:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_dark_blue);
		break;
	case select_turquoise:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_turquoise);
		break;
	case select_dark_green:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_dark_green);
		break;
	case select_light_blue:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_light_blue);
		break;
	case select_purple:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_purple);
		break;
	case select_yellow:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_yellow);
		break;
	case select_swampy:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_swampy);
		break;
	default:
		cout << " I don`t know this kind of color " << endl;
		break;
	}
	glFlush();
	glutPostRedisplay();
}

void fill_of_figure_func(int value) {
	switch (value) {
	case select_fill:
		arr_fig[selector_figure_active_now]->active_figure_fill(select_fill);
		break;
	case select_empty:
		arr_fig[selector_figure_active_now]->active_figure_fill(select_empty);
		break;
	default:
		cout << " I don`t know this kind of fill " << endl;
		break;
	}
	glFlush();
	glutPostRedisplay();
}

void clarity_of_figure_func(int value) {
	switch (value) {
	case select_view:
		arr_fig[selector_figure_active_now]->active_figure_clarity(select_view);
		break;
	case select_hidden:
		arr_fig[selector_figure_active_now]->active_figure_clarity(select_hidden);
		break;
	default:
		cout << " I don`t know this kind of clarity " << endl;
		break;
	}
	glFlush();
	glutPostRedisplay();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
