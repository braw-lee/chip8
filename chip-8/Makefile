a: main.cpp chip8.o display.o keyboard.o eventHandler.o randomNumber.o decodeAndExecute.o utility.o
	g++ main.cpp chip8.o display.o keyboard.o eventHandler.o randomNumber.o decodeAndExecute.o utility.o -o a -Wall -lSDL2
	
chip8.o: chip8.cpp chip8.h
	g++ -c chip8.cpp -Wall -lSDL2 
decodeAndExecute.o: decodeAndExecute.cpp chip8.h config.h
	g++ -c decodeAndExecute.cpp -Wall -lSDL2 
display.o: display.cpp display.h
	g++ -c display.cpp -Wall -lSDL2 
eventHandler.o: eventHandler.cpp eventHandler.h
	g++ -c eventHandler.cpp -Wall 
keyboard.o: keyboard.cpp
	g++ -c keyboard.cpp -Wall 
randomNumber.o: randomNumber.cpp
	g++ -c randomNumber.cpp -Wall 
utility.o: utility.cpp
	g++ -c utility.cpp -Wall 
clean:
	rm *.o
