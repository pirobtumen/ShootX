GCC = g++
LIB = ./lib/
SRC = ./src/

MAIN_FILE = shoot-x

build/$(MAIN_FILE): $(SRC)$(MAIN_FILE).cpp $(LIB)Vector/Vector.hpp
	$(GCC) -o $@ $(SRC)$(MAIN_FILE).cpp -lX11 -I$(LIB)