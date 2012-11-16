CXX = g++
CXXFLAGS = -std=gnu++0x -O4

build-exec = $(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: all clean

all: encoder decoder checker
clean: ; rm -f *.cnf *.ans *.out ./*.o ./*.gch encoder decoder checker

%.o: %.cpp ; $(CXX) $(CXXFLAGS) -c $<

encoder: encoder.o ; $(build-exec)
	
encoder.o: encoder.cpp

decoder: decoder.o ;  $(build-exec)

decoder.o: decoder.cpp

checker: checker.o ; $(build-exec)

checker.o: checker.cpp
