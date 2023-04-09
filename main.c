#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <curses.h>

#define CHAR_ASPECT 9.0 / 20.0
#define GRADIENT_LENGTH 66

const char* GRADIENT = ".`,:;i1|tLs_-+^~ \"I<>l?7jvcft/\\()=~#<>Xz{[]}$bmwqpdbkhao*#MW&8%B@$";

double convert_number(uint32_t number, uint32_t max)
{
	return (number - ((double)max / 2.0)) / ((double)max / 4.0);
}

void to_square(double* a, double* b, double* orig_a, double* orig_b)
{
	double temp = (*a * *a) - (*b * *b);
	*b = 2.0 * *a * *b;
	*a = temp;

	*a += *orig_a;
	*b += *orig_b;
}

double magn(double a, double b)
{
	return sqrt(a * a + b * b);
}

char* calculate_set(uint16_t WIDTH, uint16_t HEIGHT, double* ZOOM, double* X_OFFSET, double* Y_OFFSET, uint32_t* MAX_ITERS)
{
	char* set = malloc((WIDTH * HEIGHT) * sizeof(char));

	double aspect = CHAR_ASPECT * ((double)WIDTH / HEIGHT);

	for (uint16_t y = 0; y < HEIGHT; y++)
	{
		double img = convert_number(y, HEIGHT);
		for (uint16_t x = 0; x < WIDTH; x++)
		{
			double real = convert_number(x, WIDTH) * aspect;

			double a = (real + *X_OFFSET / *ZOOM) * *ZOOM;
			double b = (img + *Y_OFFSET / *ZOOM) * *ZOOM;

			double orig_a = a;
			double orig_b = b;

			uint32_t it = 0;
			do
			{
				it++;
				to_square(&a, &b, &orig_a, &orig_b);
				if (magn(a, b) > 2.0) break;

			} while (it < *MAX_ITERS - 1);

			set[WIDTH * y + x] = GRADIENT[(uint32_t)(GRADIENT_LENGTH * ((double)it / *MAX_ITERS))];
		}
	}
	return set;	
}

	

int main()
{
	initscr();
	curs_set(0);

	uint16_t WIDTH;
	uint16_t HEIGHT;
	uint32_t MAX_ITERS = 256;
	double ZOOM = 1.0;
	double X_OFFSET = 0.0;
	double Y_OFFSET = 0.0;
	
	while (true)
	{
		getmaxyx(stdscr, HEIGHT, WIDTH);

		char* set = calculate_set(WIDTH, HEIGHT, &ZOOM, &X_OFFSET, &Y_OFFSET, &MAX_ITERS);
		mvaddstr(0,0,set);
		free(set);

		refresh();
		
		char key= getch();
		flushinp();

		switch(key)
		{
			case 'q': endwin(); curs_set(1); return 0; break;
			case 'h': X_OFFSET -= 0.1 * ZOOM; break; 
			case 'j': Y_OFFSET += 0.1 * ZOOM; break;
			case 'k': Y_OFFSET -= 0.1 * ZOOM; break;
			case 'l': X_OFFSET += 0.1 * ZOOM; break;
			case 'd': ZOOM *= 0.9; break;
			case 'f': ZOOM *= 1.1; break;
			case 'u': MAX_ITERS *= 2; break;
			case 'i': MAX_ITERS /= 2; break;
		}
	}
}


