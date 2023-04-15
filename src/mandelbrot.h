#include <stdint.h>

#define CHAR_ASPECT 9.0 / 20.0

const char GRADIENT[] = ".`,:;i1|tLs_-+^~ \"I<>l?7jvcft/\\()=~#<>Xz{[]}$bmwqpdbkhao*#MW&8%B@$";
const uint8_t GRADIENT_LENGTH = sizeof(GRADIENT) - 1;

uint16_t WIDTH = 0;
uint16_t HEIGHT = 0;

uint32_t MAX_ITERS = 256;
double ZOOM = 1.0;
double X_OFFSET = 0.0;
double Y_OFFSET = 0.0;
