CC = g++

all:  lrucache.o
	$(CC) -o lrutester lrutester.cpp lrucache.o
lrucache.o: lrucache.cpp lrucache.h 
	$(CC) -c lrucache.cpp

clean:
	rm lrutester.o 
	rm lrucache.o
	rm lrutester

