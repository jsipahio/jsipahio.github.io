CPP=g++
OPT=-Wall -Wshadow -Wunused -Wuninitialized

main: BankAccount.o main.o
	$(CPP) $(OPT) BankAccount.o main.o -o main

BankAccount.o: BankAccount.hpp BankAccount.cpp
	$(CPP) $(OPT) -c BankAccount.cpp -o BankAccount.o

main.o: BankAccount.hpp main.cpp 
	$(CPP) $(OPT) -c main.cpp -o main.o

clean:
	rm -r *.o main