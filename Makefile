pe-vector-tests: main.cpp pe-vector.hpp
	clang++ -Wall -Wextra -Weffc++ -std=c++14 -o pe-vector-tests main.cpp