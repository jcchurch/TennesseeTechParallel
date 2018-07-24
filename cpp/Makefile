CC = gcc
CPP = g++
CFLAGS = -Wall -fopenmp
RM = rm
TARGET = hello confirm gameOfLife arraySum arrayMax

all: $(TARGET)

confirm: confirm.cpp
	$(CPP) $(CFLAGS) -o $@ $<

gameOfLife: gameOfLife.cpp
	$(CPP) $(CFLAGS) -o $@ $<

hello: hello.cpp
	$(CPP) $(CFLAGS) -o $@ $<

arraySum: arraySum.cpp
	$(CPP) $(CFLAGS) -o $@ $<

arrayMax: arrayMax.cpp
	$(CPP) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(TARGET)
