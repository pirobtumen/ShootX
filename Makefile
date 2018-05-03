GCC = g++
SRC = ./src/

MAIN_FILE = xshoot

build/$(MAIN_FILE): $(SRC)$(MAIN_FILE).cpp
	$(GCC) -o $@ $(SRC)$(MAIN_FILE).cpp -lX11
