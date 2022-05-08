CC := g++
CFLAGS := -Wall -g
TARGET := main

SRCS := $(wildcard *.cc)
OBJS := $(patsubst %.cc,%.o,$(SRCS))

o: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
c: $(TARGET)
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o
	
.PHONY: all clean

clean:
	rm -rf $(TARGET) *.o *.out

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./main