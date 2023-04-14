#include <stdlib.h>
#include <curses.h>
#include <locale.h>

char* calculate_set(uint16_t WIDTH, uint16_t HEIGHT);
void control_mandelbrot(char key);

int main()
{
	setlocale(LC_ALL, "en_US.UTF-8");
	initscr();
	curs_set(0);

	while (true)
	{
		uint16_t WIDTH;
	    uint16_t HEIGHT;
	    getmaxyx(stdscr, HEIGHT, WIDTH); // get COLS and ROWS


		char* set = calculate_set(WIDTH, HEIGHT);
		mvaddstr(0,0,set); // print set to 0x 0y
		free(set);

		refresh();
		
		char key = getch();
		flushinp();

		if (key == 'q')
			break;
		else
			control_mandelbrot(key);
	}
	endwin();
	curs_set(1);
	return 0;
}


