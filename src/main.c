#include <stdlib.h>
#include <curses.h>

extern uint16_t WIDTH;
extern uint16_t HEIGHT;

void set_size(uint16_t W, uint16_t H);
void calculate_set(char* set);
void control_mandelbrot(char key);

int main()
{
	initscr();
	curs_set(0);

	uint16_t new_W, new_H;
	char* set;

	while (true)
	{
		getmaxyx(stdscr, new_H, new_W); // get COLS and ROWS
		if (new_W != WIDTH || new_H != HEIGHT)
		{
			WIDTH = new_W;
			HEIGHT = new_H;
			set = malloc((WIDTH * HEIGHT + 1) * sizeof(char));
		}

		calculate_set(set);
		mvaddstr(0, 0, set); // print set to 0x 0y

		refresh();
		
		char key = getch();
		flushinp();

		if (key == 'q')
			break;
		else
			control_mandelbrot(key);
	}
	free(set);

	endwin();
	curs_set(1);
	return 0;
}


