TARGET = mandel
LIBS = -lncurses 
LDFLAGS = $(LIBS)

SRC_DIR = src
VPATH = $(SRC_DIR)

$(TARGET): main.o mandelbrot.o
	$(CC) -o $@ $(SRC_DIR)/main.o $(SRC_DIR)/mandelbrot.o $(LDFLAGS) 

main.o: main.c
	$(CC) -c -o $(SRC_DIR)/$@ $< 

mandelbrot.o: mandelbrot.c mandelbrot.h
	$(CC) -c -o $(SRC_DIR)/$@ $< 

clean:
	$(RM) $(SRC_DIR)/*.o
	$(RM) $(TARGET)
