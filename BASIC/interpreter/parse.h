#ifndef PARSE_HPP
#define PARSE_HPP

#include "arithmetic.h"
#include "boolean.h"
#include "command.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h> 	//atoi

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

#endif