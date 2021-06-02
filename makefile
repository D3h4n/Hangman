CC = gcc
CFLAGS = -std=c99 -Wall
TARGET = hangman
OBJS = main.o hangman.o settings.o

${TARGET}: ${OBJS}
	${CC} ${CFLAGS} $^ -o $@

%.o: %.c %.h
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o ${TARGET} words
