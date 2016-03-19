# Makefile for Trandom*.cpp file
# compiled with g++
# libraries linked to root
# make sure you have ROOT environment setup before running this file

all: Trandom.out Trandom2.out Trandom3.out Trandom4.out Trandom5.out Trandom6.out	


Trandom.out:
	 g++ -c `root-config --cflags` Trandom.cpp
	 g++ -o Trandom.out `root-config --libs` Trandom.o

Trandom2.out:
	 g++ -c `root-config --cflags` Trandom2.cpp
	 g++ -o Trandom2.out `root-config --libs` Trandom2.o

Trandom3.out:
	 g++ -c `root-config --cflags` Trandom3.cpp
	 g++ -o Trandom3.out `root-config --libs` Trandom3.o

Trandom4.out:
	 g++ -c `root-config --cflags` Trandom4.cpp
	 g++ -o Trandom4.out `root-config --libs` Trandom4.o

Trandom5.out:
	 g++ -c `root-config --cflags` Trandom5.cpp
	 g++ -o Trandom5.out `root-config --libs` Trandom5.o

Trandom6.out:
	 g++ -c `root-config --cflags` Trandom6.cpp
	 g++ -o Trandom6.out `root-config --libs` Trandom6.o
