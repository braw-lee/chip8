cmake_minimum_required(VERSION 3.22.1)
project(Project-1 LANGUAGES CXX)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable( mainBinary 
	src/main.cpp 

	src/cpu.cpp 
	src/decodeAndExecute.cpp 
	src/display.cpp
	src/eventHandler.cpp
	src/keyboard.cpp
	src/machine.cpp
	src/randomNumber.cpp
	src/sound.cpp
	src/utility.cpp
	)
target_compile_features(mainBinary PRIVATE cxx_std_11)
target_include_directories(mainBinary PRIVATE $(CMAKE_CURRENT_SOURCE_DIR)/include)
target_link_libraries(mainBinary ${SDL2_LIBRARIES})
