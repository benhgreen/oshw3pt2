all: myult

myult: myult.c myult.h
	gcc myult.c -pthread -std=c99 -o myult

clean:
	rm myult