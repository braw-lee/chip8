# Project title : CHIP-8 emulator
This is a CHIP-8 emulator made with C++ and SDL2 . CMake is used to compile the project.
A learning project.

---

### Pre-requisites
GCC (C++ compiler), SDL2 (a graphics library), CMake (a build file generator)

Clone the project and type following commands to build the project
```
mkdir build && cd build
cmake ..
make
```
You should have an executable named mainBinary .

Run it like this
```
./mainBinary <chip8_rom_path>
```
### Screenshots
Some games that can be run on this emulator:
- Tank
![image link err](./docs/images/tank.png)
- Tetris
![image link err](./docs/images/tetris.png)
- Tic tac toe
![image link err](./docs/images/tic_tac_toe.png)
- Space invaders
![image link err](./docs/images/space_invaders_logo.png)
![image link err](./docs/images/space_invaders.png)

Also used [chip8 test suite](https://github.com/Timendus/chip8-test-suite) to test the emulator
![image link err](./docs/images/test_suit.png)

### References and sources :

1. https://tobiasvl.github.io/blog/write-a-chip-8-emulator
	- Used it as the main refrence for the project, it tells everything you need to know about CHIP-8 emulator.
2. http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
	- Used it as second reference.
3. https://wiki.libsdl.org/SDL2
	- Used to refer to SDL2 API.
4. https://chip-8.github.io/extensions
	- Used to differentiate between original and modern version, helpful in correcting ambiguous instructions.
5. https://github.com/Timendus/chip8-test-suite
	- Used to test CHIP-8 emulator, very helpul in getting the expected behaviour from instructions.
