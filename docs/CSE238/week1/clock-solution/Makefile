CPP=g++
OPT=-Wall -Wshadow -Wunused -Wuninitialized

clock: clock.o main.o
	$(CPP) $(OPT) clock.o main.o -o clock

clock.o: clock.hpp clock.cpp
	$(CPP) $(OPT) -c clock.cpp -o clock.o

main.o: clock.hpp main.cpp 
	$(CPP) $(OPT) -c main.cpp -o main.o

clean:
	rm -r *.o clock