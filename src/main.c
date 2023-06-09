#include <stdlib.h>
#include <curses.h>

void set_size(uint16_t W, uint16_t H);
void calculate_set(char* set);
void control_mandelbrot(char key);

int main()
{
	initscr();
	curs_set(0);

	int old_W, old_H;
	char* set = NULL;

	while (true)
	{
		if (old_W != COLS || old_H != LINES)
		{
			old_W = COLS;
			old_H = LINES;
			free(set);
			set = malloc((COLS * LINES + 1) * sizeof(char));
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


