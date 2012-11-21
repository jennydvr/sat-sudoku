CXX = g++
CXXFLAGS = -std=gnu++0x -O4

build-exec = $(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: all clean

all: encoder decoder
clean: ; rm -f *.cnf *.ans *.out ./*.o ./*.gch encoder decoder

%.o: %.cpp ; $(CXX) $(CXXFLAGS) -c $<

encoder: encoder.o ; $(build-exec)
	
encoder.o: encoder.cpp

decoder: decoder.o ;  $(build-exec)

decoder.o: decoder.cpp
