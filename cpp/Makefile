CC = gcc
CPP = g++
CFLAGS = -Wall -fopenmp
RM = rm
TARGET = hello confirm gameOfLife arraySum arrayMax arraySumReduction arrayMaxReduction hflip gray pipeline

all: $(TARGET)

pipeline: pipeline.cpp libppm.cpp
	$(CPP) $(CFLAGS) -o $@ $< libppm.cpp

gray: gray.cpp libppm.cpp
	$(CPP) $(CFLAGS) -o $@ $< libppm.cpp

hflip: hflip.cpp libppm.cpp
	$(CPP) $(CFLAGS) -o $@ $< libppm.cpp

.cpp:
	$(CPP) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(TARGET)
