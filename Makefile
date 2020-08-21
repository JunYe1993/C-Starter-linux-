# config
CC      = gcc
CFLAGS  = -g -Wall

# path
SOURCE  = source/
INCLUDE = include/
OBJECTS = myRegex.o

all: program

program: main.o ${OBJECTS}
	${CC} ${CFLAGS} -o program main.o ${OBJECTS} -lpthread

main.o: main.c
	${CC} -I${INCLUDE} ${CFLAGS} -c $< 

%.o: ${SOURCE}%.c ${INCLUDE}%.h
	${CC} -I${INCLUDE} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f main.o ${OBJECTS} program