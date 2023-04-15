#include "mandelbrot.h"

void set_size(uint16_t W, uint16_t H)
{
	WIDTH = W;
	HEIGHT = H;
}

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

void calculate_set(char* set)
{
    double aspect = CHAR_ASPECT * ((double)WIDTH / HEIGHT);

    for (uint16_t y = 0; y < HEIGHT; y++)
    {
        double img = convert_number(y, HEIGHT);
        for (uint16_t x = 0; x < WIDTH; x++)
        {
            double real = convert_number(x, WIDTH) * aspect;

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

            set[WIDTH * y + x] = GRADIENT[(uint32_t)(GRADIENT_LENGTH * ((double)it / MAX_ITERS))];
        }
    }
	set[WIDTH * HEIGHT] = '\0';
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

    
