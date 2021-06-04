CXX ?=g++
MAIN = ./test/test.cpp
TAR = test
DEBUG ?= 1

test:$(MAIN) 
	$(CXX) -o $(TAR) $^ -g

clean:
	rm -rf $(TAR)