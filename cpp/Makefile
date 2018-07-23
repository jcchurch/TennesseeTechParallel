CC = gcc
CPP = g++
CFLAGS = -Wall -fopenmp
RM = rm

all: hello confirm gameOfLife arraySum

confirm: confirm.cpp
	$(CPP) $(CFLAGS) -o $@ $<

gameOfLife: gameOfLife.cpp
	$(CPP) $(CFLAGS) -o $@ $<

hello: hello.cpp
	$(CPP) $(CFLAGS) -o $@ $<

arraySum: arraySum.cpp
	$(CPP) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(TARGET)
