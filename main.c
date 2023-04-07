#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <curses.h>

#define CHAR_ASPECT 9.0 / 20.0

const char* GRADIENT = ".`,:;i1|tLs_-+^~ \"I<>l?7jvcft/\\()=~#<>Xz{[]}$bmwqpdbkhao*#MW&8%B@$";

uint8_t get_str_length(const char* str)
{
	uint8_t i = 0;
	while (*(str + i) != '\0')
		i++;

	return i;
}

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
	uint8_t grad_length = get_str_length(GRADIENT);
	char* set = malloc(WIDTH * HEIGHT);

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

			set[WIDTH * y + x] = GRADIENT[(uint32_t)(grad_length * ((double)it / *MAX_ITERS))];
		}
	}
	return set;	
}

	

int main()
{
	initscr();
	curs_set(1);


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

		if (key == 'q') break;
		else if (key == 'h') X_OFFSET -= 0.1 * ZOOM;
		else if (key == 'j') Y_OFFSET += 0.1 * ZOOM;
		else if (key == 'k') Y_OFFSET -= 0.1 * ZOOM;
		else if (key == 'l') X_OFFSET += 0.1 * ZOOM;
		else if (key == 'd') ZOOM *= 0.9;
		else if (key == 'f') ZOOM *= 1.1;
		else if (key == 'u') MAX_ITERS *= 2;
		else if (key == 'i') MAX_ITERS /= 2;

	}
	endwin();
	return 0;

}


