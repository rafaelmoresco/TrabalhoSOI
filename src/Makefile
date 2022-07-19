IDIR =.
CC=g++
LDLIBS =  -lsfml-graphics -lsfml-window -lsfml-system -lm  -lpng
CFLAGS=-I$(IDIR) -g -Wextra

LDFLAGS= $(CFLAGS)

ODIR=.
LIBS= $(LDLIBS) $(LDFLAGS)

_DEPS = window.h main_class.h char.h pacman.h ghost.h game.h interface.h enum.h keyinput.h keyevent.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

SDIR = os

_os = thread.h system.h semaphore.h cpu.h debug.h traits.h
os = $(patsubst %,$(SDIR)/%,$(_os))

_OBJ = main.o window.o main_class.o thread.o system.o semaphore.o cpu.o debug.o char.o pacman.o ghost.o game.o interface.o keyinput.o keyevent.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -std=c++14 -c -o $@ $< $(CFLAGS) -Wextra

$(ODIR)/%.o: %.c $(os)
	$(CC) -std=c++14 -c -o $@ $< -Wextra

main: $(OBJ)
	$(CC) -std=c++14 -o $@ $^ $(CFLAGS) $(LIBS)

cpu.o: os/cpu.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
system.o: os/system.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
thread.o: os/thread.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
semaphore.o: os/semaphore.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
debug.o: os/debug.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
main_class.o: main_class.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	
valgrind:
	valgrind --tool=memcheck --leak-check=yes ./main
