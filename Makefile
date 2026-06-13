build:
	gcc -Wall -std=c99 $(shell pkg-config --cflags sdl2) ./src/*.c $(shell pkg-config --libs sdl2) -o renderer

run:
	./renderer

clean:
	rm renderer
