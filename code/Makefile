#gcc -o bin/executable src/main.c  `sdl2-config --cflags --libs` `pkg-config --cflags --libs SDL2_image`

GC=gcc
CFLAGS=-O2 -Wall
LIBS=`sdl2-config --cflags --libs` `pkg-config --cflags --libs SDL2_image` `pkg-config --cflags --libs SDL2_ttf`

rummikub: moha.o 
	$(GC) $(CFLAGS)  src/moha.o src/main.c -o rummikub $(LIBS)

moha.o:
	$(GC) $(CFLAGS) -o src/moha.o -c src/moha.c

clean:
	rm -f src/*.o
	rm -f rummikub

exe: rummikub
	./rummikub