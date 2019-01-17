CC      = g++
CFLAGS  = -g -pthread -O0 -std=c++11 -Wall


OBJECTS = FileHandler.o Merger.o Processor.o Threader.o

all: Program

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

Program: $(OBJECTS) Main.o
	$(CC) $(OBJECTS) Main.o -pthread -o psiY

clean: 
	rm -f *.o $(PROGRAM)
