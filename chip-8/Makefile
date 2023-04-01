a: main.cpp chip8.o display.o keyboard.o eventHandler.o
	g++ main.cpp chip8.o display.o keyboard.o eventHandler.o -o a -Wall -lSDL2 -g
chip8.o: chip8.cpp chip8.h
	g++ -c chip8.cpp -Wall -lSDL2 -g
display.o: display.cpp display.h
	g++ -c display.cpp -Wall -lSDL2 -g
eventHandler.o: eventHandler.cpp eventHandler.h
	g++ -c eventHandler.cpp -Wall -g
keyboard.o: keyboard.cpp
	g++ -c keyboard.cpp -Wall -g
clean:
	rm *.o
