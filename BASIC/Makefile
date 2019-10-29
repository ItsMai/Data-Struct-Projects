all: boolean.o arithmetic.o command.o interpreter.o basic_interpreter

basic_interpreter: main.cpp interpreter.o command.o arithmetic.o boolean.o parse.o
	 g++ -g -Wall -std=c++11 main.cpp -o basic_interpreter interpreter.o command.o arithmetic.o boolean.o parse.o

interpreter.o: interpreter/interpreter.cpp interpreter/interpreter.h 
	g++ -g -Wall -c -std=c++11 $< -o interpreter.o

command.o: interpreter/command.cpp interpreter/command.h 
	g++ -g -Wall -c -std=c++11 $< -o command.o

arithmetic.o: interpreter/arithmetic.cpp interpreter/arithmetic.h 
	g++ -g -Wall -c -std=c++11 $< -o arithmetic.o

boolean.o: interpreter/boolean.cpp interpreter/boolean.h 
	g++ -g -Wall -c -std=c++11 $< -o boolean.o

parse.o : interpreter/parse.cpp interpreter/parse.h
		g++ -g -Wall -c -std=c++11 $< -o parse.o

