CC     = gcc
CFLAGS = -m32 -std=gnu11 -Wall -g
OBJ    = a03.o
EXE    = a03p

all: $(OBJ)
	clear
	clear
	$(CC) $(CFLAGS) -lm -o $(EXE) $^

e: $(OBJ)
	clear
	clear
	$(CC) $(CFLAGS) -lm -o $(EXE) $^
	rm -f *.o
	valgrind --leak-check=yes ./$(EXE)

f: $(OBJ)
	clear
	clear
	$(CC) $(CFLAGS) -lm -o $(EXE) $^
	rm -f *.o
	./$(EXE) 11 22 33 44 0 

o: $(OBJ)
	clear
	clear
	$(CC) -g -c $(OBJ)
	objdump -d -M intel -S obj.c
