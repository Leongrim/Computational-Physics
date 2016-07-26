CC = g++
PY = python
CFLAGS = -std=c++11 -Wall -O3 -march=native -c 
LDFLAGS = -fopenmp
AUFGABE1_SOURCES = Aufgabe1.cpp
AUFGABE2_SOURCES = Aufgabe2.cpp

AUFGABE1_OBJECTS = $(AUFGABE1_SOURCES:.cpp=.o)
AUFGABE2_OBJECTS = $(AUFGABE2_SOURCES:.cpp=.o)

EXECUTABLE = program1
AUFGABE2_EXECUTABLE = program2

.PHONY: all aufgabe1 aufgabe2

all: aufgabe1 aufgabe2

aufgabe1: $(EXECUTABLE)

aufgabe2: $(AUFGABE2_EXECUTABLE)


$(EXECUTABLE): $(AUFGABE1_OBJECTS)
	$(CC) -o $@ $(AUFGABE1_OBJECTS) $(LDFLAGS)

$(AUFGABE2_EXECUTABLE): $(AUFGABE2_OBJECTS)
	$(CC) -o $@ $(AUFGABE2_OBJECTS) $(LDFLAGS)  

.cpp.o:
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@