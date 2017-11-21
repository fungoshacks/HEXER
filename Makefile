CC=g++
CFLAGS=-std=c++11
DEPS = Mutator.cpp Mutation.cpp MutationFactory.cpp ProcessMonitor.cpp ByteReplace.cpp ByteInvert.cpp BitFlip.cpp main.cpp
OBJ = main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hexer: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

