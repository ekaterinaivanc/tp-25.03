CXXFLAGS += -Wall -Weffc++ -std=c++14

UNIT_TESTS = pe-vector-tests
OBJS = main.o

$(UNIT_TESTS): $(OBJS)
	clang++ -o $@ $^

clean:
	rm $(UNIT_TESTS) $(OBJS)
