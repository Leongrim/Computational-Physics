CC = g++ -I /home/leonard/FP_Repo2016/Computational-Physics/Blatt-09/build_dir/
PY = python
CFLAGS = -std=c++11 -Wall -O3 -march=native -c
LDFLAGS =
AUFGABE1_SOURCES = Aufgabe1.cpp
#AUFGABE2_SOURCES = Aufgabe2.cpp

AUFGABE1_OBJECTS = $(AUFGABE1_SOURCES:.cpp=.o)
#AUFGABE2_OBJECTS = $(AUFGABE2_SOURCES:.cpp=.o)

EXECUTABLE = program1

.PHONY: all aufgabe1 

all: aufgabe1

aufgabe1: $(EXECUTABLE)

$(EXECUTABLE): $(AUFGABE1_OBJECTS)
	$(CC) -o $@ $(AUFGABE1_OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@