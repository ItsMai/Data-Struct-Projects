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
    virtual bool get_result(){return false;}
protected:
    bool result_ = false;
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
};



#endif