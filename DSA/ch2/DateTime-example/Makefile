CPP=g++
OPTS=-g -Werror -W -Wunused -Wuninitialized -Wshadow -std=c++20 

TESTS = test_default_constructor test_TimeParts_constructor test_now test_operator_equals test_operator_plus test_operator_minus test_toString

default: 
	@echo 'Options:'
	@echo '- DateTime.o'
	@echo '- tests'
	@echo '- clean'

DateTime.o: DateTime.hpp DateTime.cpp
	$(CPP) $(OPTS) -c DateTime.cpp -o DateTime.o 

tests: $(TESTS)
	./test_default_constructor
	./test_TimeParts_constructor
	./test_now
	./test_operator_equals
	./test_operator_plus
	./test_operator_minus
	./test_toString

test_%: test_%.o DateTime.o 
	$(CPP) $(OPTS) DateTime.o test_$*.o -o test_$* 

test_%.o: test_%.cpp DateTime.hpp 
	$(CPP) $(OPTS) -c test_$*.cpp -o test_$*.o

clean:
	rm -rf *.o $(TESTS)
