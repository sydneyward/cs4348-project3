#this is the makefile for project 3

CXX = g++

.PHONY: clean

proj3.exe: project3.o
	$(CXX) -o proj3.exe project3.o

project3.o: project3.cc
	$(CXX) -c project3.cc

clean:
	rm *.o *~ *.exe
