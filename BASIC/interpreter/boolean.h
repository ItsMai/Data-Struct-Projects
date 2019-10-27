#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include "arithmetic.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>


class BooleanExpression{
public:
    virtual ~BooleanExpression() {}
    virtual std::string format() const = 0;
};

//BOOLEAN FUNCTIONS
/*
this returns true if the values of the numeric expressions are the same
*/
class EqualsExpression : public BooleanExpression {
public:
    EqualsExpression(NumericExpression* left, NumericExpression* right);
    virtual~EqualsExpression();
    virtual std::string format() const;
    bool get_result();
    

private:
    NumericExpression* left;
    NumericExpression* right;
    bool result_ = false;
};
/*
Returns true if the left is greater than the right STRICLY 
*/
class GreaterExpression : public BooleanExpression {
public:
    GreaterExpression(NumericExpression* left, NumericExpression* right);
    virtual~GreaterExpression();
    virtual std::string format() const;
    bool get_result();

private:
    NumericExpression* left;
    NumericExpression* right;
    bool result_ = false;
};
/*
Returns true if the left is less than the right STRICLY 
*/
class LessExpression : public BooleanExpression {
public:
    LessExpression(NumericExpression* left, NumericExpression* right);
    virtual~LessExpression();
    virtual std::string format() const;
    bool get_result();

private:
    NumericExpression* left;
    NumericExpression* right;
    bool result_ = false;
};



#endif