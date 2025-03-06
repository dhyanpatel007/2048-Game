cc = gcc
CFLAGS = -Wall -g
OBJ = game2048.o utility.o

game2048: $(OBJ)
	$(CC) $(CFLAGS) -o game2048 $(OBJ)

game2048.o: game2048.c utility.h
	$(CC) $(CFLAGS) -c game2048.c

utility.o: utility.c utility.h
	$(CC) $(CFLAGS) -c utility.c

clean:
	rm -f game2048 $(OBJ)
