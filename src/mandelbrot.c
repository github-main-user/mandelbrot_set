#include "mandelbrot.h"
#include <stdlib.h>

double convert_number(uint32_t number, uint32_t max)
{
    return (number - ((double)max / 2.0)) / ((double)max / 4.0);
}

void to_square(double* a, double* b)
{
    double temp = (*a * *a) - (*b * *b);
    *b = 2.0 * *a * *b;
    *a = temp;
}

uint32_t get_iters(double img, double real)
{
	double a = (real + X_OFFSET / ZOOM) * ZOOM;
	double b = (img + Y_OFFSET / ZOOM) * ZOOM;

	double old_a = a;
	double old_b = b;

	int32_t it;
	for (it = 0; it < MAX_ITERS - 1; it++)
	{
		to_square(&a, &b);
		a += old_a;
		b += old_b;
		//    (a^2 + b^2)	  2^2
		if ((a * a + b * b) > 4.0) break;
	}
	return it;
}

char* calculate_set(uint16_t WIDTH, uint16_t HEIGHT)
{
	double img, real;
    char* set = malloc(((WIDTH * HEIGHT) * UTF_SYMBOL_SIZE + 1) * sizeof(char));

	ASPECT = CHAR_ASPECT * ((double)WIDTH / HEIGHT);

    for (uint16_t y = 0; y < HEIGHT * 4; y += 4)
    {
        for (uint16_t x = 0; x < WIDTH * 2; x += 2)
        {	
			uint32_t it;
			uint8_t byte = 0; 

			for (uint16_t iy = 0; iy < 4; iy++)
			{
				img = convert_number(y+iy, HEIGHT * 4);
				for (uint16_t ix = 0; ix < 2; ix++)
				{
					real = convert_number(x+ix, WIDTH * 2) * ASPECT;
					it = get_iters(img, real);

					byte <<= 1;

					if (it > MAX_ITERS / 2)
						byte |= 1;
				}
			}
				
			uint16_t true_x = x / 2; 
			uint16_t true_y = y / 4;

			for (uint8_t i = 0; i < 3; i++)
				set[(WIDTH * true_y  + true_x) * UTF_SYMBOL_SIZE + i] = BRAILLES[byte * UTF_SYMBOL_SIZE + i];
        }
    }
	set[(WIDTH * HEIGHT) * UTF_SYMBOL_SIZE] = '\0';
    return set; 
}

void control_mandelbrot(char key)
{
    switch(key)
        {
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

    
