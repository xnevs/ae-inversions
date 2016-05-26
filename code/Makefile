CXX=g++
CXX_FLAGS=-std=c++14 -O3 -march=native -mtune=native -Wall -Wextra -Wshadow

test: build/test_inversions.o build/inversions.o
	$(CXX) $(CXX_FLAGS) -o inversions build/test_inversions.o build/inversions.o

build/test_inversions.o: src/test_inversions.cpp src/test_utilities.hpp src/inversions.hpp build
	$(CXX) $(CXX_FLAGS) -c -o build/test_inversions.o src/test_inversions.cpp

build/inversions.o: src/inversions.cpp src/inversions.hpp build
	$(CXX) $(CXX_FLAGS) -c -o build/inversions.o src/inversions.cpp

build:
	mkdir build

.PHONY: clean
clean:
	rm build/*.o
	rmdir build
