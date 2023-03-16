a: main.cpp chip8.o display.o
	g++ main.cpp chip8.o display.o -o a -Wall -lSDL2 -g
chip8.o: chip8.cpp chip8.h
	g++ -c chip8.cpp -Wall -lSDL2 -g
display.o: display.cpp display.h
	g++ -c display.cpp -Wall -lSDL2 -g
clean:
	rm *.o
