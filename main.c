#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <curses.h>

#define CHAR_ASPECT 9.0 / 20.0

const char* GRADIENT = ".`,:;i1|tLs_-+^~ \"I<>l?7jvcft/\\()=~#<>Xz{[]}$bmwqpdbkhao*#MW&8%B@$";
const uint32_t MAX_ITERS = 256;

uint8_t get_str_length(const char* str)
{
	uint8_t i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
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

char* calculate_set(uint16_t width, uint16_t height)
{
	uint8_t grad_length = get_str_length(GRADIENT);
	char* set = malloc(width * height);

	double aspect = CHAR_ASPECT * ((double)width / height);

	for (uint16_t y = 0; y < height; y++)
	{
		double img = convert_number(y, height);
		for (uint16_t x = 0; x < width; x++)
		{
			double real = convert_number(x, width);

			double a = real * aspect;
			double b = img;

			double orig_a = a;
			double orig_b = b;

			uint32_t it = 0;
			do
			{
				it++;
				to_square(&a, &b, &orig_a, &orig_b);
				if (magn(a, b) > 2.0) break;

			} while (it < MAX_ITERS - 1);

			set[width * y + x] = GRADIENT[(uint32_t)(grad_length * ((double)it / MAX_ITERS))];
		}
	}
	return set;	
}

	

int main()
{
	initscr();
	curs_set(1);


	uint16_t width;
	uint16_t height;
	getmaxyx(stdscr, height, width);

	char* set = calculate_set(width, height);
	printw(set);
	refresh();
	
	getch();

	endwin();
	return 0;

}


