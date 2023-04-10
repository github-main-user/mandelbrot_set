LIBS=-lncurses -lm

mandel: main.o mandelbrot.o
	$(CC) -o mandel src/main.o src/mandelbrot.o $(LIBS)

main.o: src/main.c
	$(CC) -c src/main.c -o src/main.o

mandelbrot.o: src/mandelbrot.c src/mandelbrot.h
	$(CC) -c src/mandelbrot.c -o src/mandelbrot.o

clean:
	$(RM) src/main.o
	$(RM) src/mandelbrot.o
