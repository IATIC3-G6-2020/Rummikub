#gcc -o bin/executable src/main.c  `sdl2-config --cflags --libs` `pkg-config --cflags --libs SDL2_image`

GC=gcc
CFLAGS=-O2 -Wall
LIBS=`sdl2-config --cflags --libs` `pkg-config --cflags --libs SDL2_image`

rummikub: test.o 
	$(GC) $(CFLAGS)  src/test.o src/main.c -o rummikub $(LIBS)

test.o:
	$(GC) $(CFLAGS) -o src/test.o -c src/test.c

clean:
	rm -f src/*.o
	rm -f rummikub

exe: rummikub
	./rummikub