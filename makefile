TARGET=mandelbrot

LIBS=-lncurses 

LDFLAGS=$(LIBS)

$(TARGET): main.o mandelbrot.o
	$(CC) -o $@ src/main.o src/mandelbrot.o $(LDFLAGS) 

main.o: src/main.c
	$(CC) -c src/main.c -o src/main.o

mandelbrot.o: src/mandelbrot.c src/mandelbrot.h
	$(CC) -c src/mandelbrot.c -o src/mandelbrot.o

clean:
	$(RM) src/*.o
	$(RM) $(TARGET)
