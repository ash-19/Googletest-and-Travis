# Snehashish Mishra and Nick Porter
# CS 3505, A4 - Testing and Travis
# Makefile for A4

# Use g++4.8 compiler on travis
# CXX ?= g++-4.8
CXX = g++

# Compiler flags
CFLAGS = -Wall -std=c++11

# Google Test directory
GOOGLETEST = ../googletest/googletest

# makes the final executable
StudentsTests: Students.o
	$(CXX) -o StudentTests $(CFLAGS) Students.o StudentsTests.cpp -L$(GOOGLETEST) -lgtest -lgtest_main -lpthread

# Removes all the .o object files and any executable files
clean:
	$(RM) count *.o *~ StudentsTests

# test executable
test:
	make StudentsTests
	./StudentsTests
