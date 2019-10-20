PROGRAM = matf-pair
CXX = g++
CXXFLAGS = -Wall -Wextra --std=c++17
LDFLAGS = -lm

$(PROGRAM): main.o
	$(CXX) $(LDFLAGS) -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o $(PROGRAM)
