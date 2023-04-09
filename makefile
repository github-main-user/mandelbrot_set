LIBS=-lncurses -lm

mandel: main.c
	$(CC) -o mandel main.c $(LIBS)
