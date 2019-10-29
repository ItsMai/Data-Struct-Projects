#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "arithmetic.h"
#include "boolean.h"
#include "command.h"
#include "parse.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h> 	//atoi
#include <map>

class Interpreter {
public:
    Interpreter(std::istream& in);
    ~Interpreter(){}
    void write(std::ostream& out);
    void functionality();
    /*
    Goes through each line and carries out the functions
    */

private:
	std::vector <std::string> out_lines;
    /*
    the vector that has all the lines of code for pretty printing
    */
    void parse(std::istream& in);
    /*
    Parses the entire input file for pretty printing and puts the numeric values 
    into pointers. Then it can be used for a functionality. 
    */
    std::map<int, Command*> line_command;
    /*
    it contains the commands that have the pointers to the required expressions
    but already has all the arthimetic and boolean done
    */
};

#endif 