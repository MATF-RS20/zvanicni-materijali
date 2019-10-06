PROGRAM = fraction
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall

$(PROGRAM): main.o Fraction.o
	$(CXX) -o $(PROGRAM) $^

Fraction.o: Fraction.cpp Fraction.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
