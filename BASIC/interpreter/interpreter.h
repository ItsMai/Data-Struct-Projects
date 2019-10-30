#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "arithmetic.h"
#include "boolean.h"
#include "command.h"
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
    NumericExpression* nexpParse(std::string, int&, int&);
    /*
    Pretty printing = Parsing numericExpression with a left and a right for pretty
    printing and for functionality.
    */
    BooleanExpression* boolParse(std::string);
    /*
    Pretty printing = Parsing boolean fucntions that will have numeric in left
    and right will have numericExpressions 
    */
    NumericExpression* parse_constant(std::string, int&, int&);
    /*
    Pretty printing = parse if it is a contant , negative and not. Puts it into 
    a numericExpression Constant
    */
    std::string parse_variable_name(std::string, int&);
    /*
    Pretty printing = parsing to find the actual variable name for specific COMMANDS
    */
    BooleanExpression* boolParse_done(std::string);
    /*
    functionality = Parsing boolean fucntions that will have numeric in left
    and right will have numericExpressions 
    */

    std:: map<std::string, NumericExpression*> int_variables;
    std:: map<std::string, std::map<int, NumericExpression* > > array_variables;
};

#endif 