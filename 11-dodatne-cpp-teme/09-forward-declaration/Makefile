PROGRAM = forward-declaration
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall

$(PROGRAM): main.o child_class.o parent_class.o
	$(CXX) -o $(PROGRAM) $^

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
