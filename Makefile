CXX = g++
CXXFLAGS = -std=gnu++0x -O4

build-exec = $(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: all clean

all: encoder
clean: ; rm -f ./*.o ./*.gch encoder

%.o: %.cpp ; $(CXX) $(CXXFLAGS) -c $<

encoder: encoder.o ; $(build-exec)
	
encoder.o: encoder.cpp
