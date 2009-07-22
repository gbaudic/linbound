# This makefile is obsolete for the current project but it did work
# I put this here for compliance with future CVS commits... it will have to be generated by automake these times^^

CXX = g++
CFLAGS = `sdl-config --cflags`
LIBS = `sdl-config --libs` -lSDL_image -lSDL_gfx -lSDL_ttf -lSDL_net
OBJS = init.cpp main.cpp main.h event.cpp error.cpp init.h image.cpp event.h gui_lb.cpp gui_lb.h update.cpp update.h

linbound : $(OBJS)
	$(CXX) -c main.cpp
	$(CXX) -c image.cpp
	$(CXX) -c error.cpp
	$(CXX) -c init.cpp
	$(CXX) -c event.cpp
	$(CXX) -c gui_lb.cpp
	$(CXX) -c update.cpp
	$(CXX) -c ./MD5_code/md5.cpp -Wall -D_XOPEN_SOURCE
	$(CXX) $(CFLAGS) image.o init.o main.o event.o error.o gui_lb.o update.o ./MD5_code/md5.o $(LIBS) -o linbound

	

install : 
	cp
	

clean : 
	rm *.o
	

uninstall : 
	rm -i
	
	
