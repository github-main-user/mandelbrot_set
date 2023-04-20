#include <stdlib.h>
#include <curses.h>

extern uint16_t WIDTH;
extern uint16_t HEIGHT;
extern uint32_t MAX_ITERS;

void set_size(uint16_t W, uint16_t H);
void calculate_set(uint32_t *set);
void control_mandelbrot(char key);

void init_colors(void)
{
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_YELLOW);
	init_pair(4, COLOR_WHITE, COLOR_BLUE);
	init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(6, COLOR_WHITE, COLOR_CYAN);
}


int main()
{
	initscr();
	start_color();
	init_colors();
	curs_set(0);

	uint16_t new_W, new_H;
	uint32_t* set = NULL;
	uint32_t set_size;

	while (true)
	{
		getmaxyx(stdscr, new_H, new_W); // get COLS and ROWS
		if (new_W != WIDTH || new_H != HEIGHT)
		{
			WIDTH = new_W;
			HEIGHT = new_H;

			if (set != NULL)
				free(set);
			set = malloc((WIDTH * HEIGHT) * sizeof(uint32_t));

			set_size = WIDTH * HEIGHT;
		}

		erase();

		calculate_set(set);
		for (int i = 0; i < set_size; i++)
		{
			uint8_t attr = 7 * (set[i] / MAX_ITERS);
			attron(COLOR_PAIR(set[i]));	
			addch(' ');
			attroff(COLOR_PAIR(set[i]));	
		}

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


