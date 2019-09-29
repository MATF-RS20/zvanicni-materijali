PROGRAM   = stl-showcase
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -Wextra

$(PROGRAM): main.o
	$(CXX) -o $(PROGRAM) main.o

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
