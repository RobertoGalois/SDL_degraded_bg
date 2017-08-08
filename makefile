.SUFFIXES:

deg: deg.o
	gcc deg.o -o deg `sdl-config --cflags --libs`
deg.o: deg.c deg.h
	 gcc -c deg.c 
