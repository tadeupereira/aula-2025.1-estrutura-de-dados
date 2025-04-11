CC = gcc
CFLAGS = -Wall -Wextra -pedantic
OBJS = main.o fila.o validacoes.o

all: callflow

callflow: $(OBJS)
	$(CC) $(CFLAGS) -o callflow $(OBJS) -lncurses

main.o: main.c fila.h validacoes.h
	$(CC) $(CFLAGS) -c main.c

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

validacoes.o: validacoes.c validacoes.h
	$(CC) $(CFLAGS) -c validacoes.c

clean:
	rm -f *.o callflow