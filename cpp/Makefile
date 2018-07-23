CC = gcc
CPP = g++
CFLAGS = -Wall -fopenmp
RM = rm

all: hello confirm gameOfLife

confirm: confirm.cpp
	$(CPP) $(CFLAGS) -o $@ $<

gameOfLife: gameOfLife.cpp
	$(CPP) $(CFLAGS) -o $@ $<

hello: hello.cpp
	$(CPP) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(TARGET)
