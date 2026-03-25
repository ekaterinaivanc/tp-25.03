CCXFLAFS += -Wall -Weffc++ -std=c++14

pe-vector-tests: main.o
	clang++ -o $@ $^