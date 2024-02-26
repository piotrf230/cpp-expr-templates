GCC = g++
GCCFLAGS = -std=c++17 -O2 -Wall -pedantic -pthread

earth-moon: earth-moon-simulation/earth-moon-simulation.cpp
	$(GCC) $(GCCFLAGS) $^ -o $@
