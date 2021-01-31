#gcc -o bin/executable src/main.c  `sdl2-config --cflags --libs` `pkg-config --cflags --libs SDL2_image`

GC=gcc
CFLAGS=-O2 -Wall
LIBS=`sdl2-config --cflags --libs` `pkg-config --cflags --libs SDL2_image` `pkg-config --cflags --libs SDL2_ttf`

rummikub: logic.o graphic.o
	$(GC) $(CFLAGS)  src/logic.o src/graphic.o src/main.c -o rummikub $(LIBS)

graphic.o:
	$(GC) $(CFLAGS) -o src/graphic.o -c src/graphic.c $(LIBS)

logic.o:
	$(GC) $(CFLAGS) -o src/logic.o -c src/logic.c

clean:
	rm -f src/*.o
	rm -f rummikub

exe: rummikub
	./rummikub