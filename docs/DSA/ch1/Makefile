CPP=g++
OPT=-Wall -Wshadow -Wunused -Wunitialized

timer: timer.o main.o
	$(CPP) $(OPT) timer.o main.o -o timer

timer.o: timer.hpp timer.cpp
	$(CPP) $(OPT) timer.cpp -o timer.o

main.o: timer.hpp main.cpp 
	$(CPP) $(OPT) main.cpp -o main.o

clean:
	rm -r *.o timer