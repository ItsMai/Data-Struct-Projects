#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>

class NumericExpression {
public:
    virtual ~NumericExpression() {}
    virtual std::string format() const = 0;
    int get_val(){return val_;}
    virtual int get_result(){return 0;}
    void set(int k){ val_ = k;}
protected:
    int val_;

};

/*
Constants can store an int and only return that value
to be used for LET command or for other expressions
*/
class Constant : public NumericExpression {
public:
    Constant(int);
    virtual ~Constant(){}
    virtual std::string format() const;
};
/*
Variables can store an int and a value
it can be set but the default is 0
*/
class IntVariable : public NumericExpression {
public:
    IntVariable(std::string);
    virtual~IntVariable(){}
    virtual std::string format() const;
    std::string get_name();
    bool is_array(){return false;}

private:
    std::string name_;
};
/*
Arrays can store the name and has an infinite amount of 
spots. If it is not set with LET then everything inside will
default to 0
*/
class ArVariable : public NumericExpression {
public:
    ArVariable(std::string, NumericExpression*);
    virtual~ArVariable();
    virtual std::string format() const;
    std::string get_name();
    bool is_array(){return true;}
private:
	std::string name_;
    NumericExpression* array_;
};
/*
Adds the left to the right but needs to be the values.
It can return the product or return the left and the right if needed.
get_sum, get_quo ....etc. user will get the values then call the function
to get the result incase of array or int or const all default results
are 0.
*/
class AdditionExpression : public NumericExpression {
public:
    AdditionExpression(NumericExpression* left, NumericExpression* right);
    virtual~AdditionExpression();
    virtual std::string format() const;
    virtual int get_result();
private:
    NumericExpression* left;
    NumericExpression* right;

};
/*
Will subtract left-right. It can return negatives.
*/
class SubtractionExpression : public NumericExpression {
public:
    SubtractionExpression(NumericExpression* left, NumericExpression* right);
    virtual~SubtractionExpression();
    virtual std::string format() const;
    virtual int get_result();

private:
    NumericExpression* left;
    NumericExpression* right;
};
/*
Division will divide the left/right. It will throw invalid_argument
if there is a 0 in the bottom.
*/
class DivisionExpression : public NumericExpression {
public:
    DivisionExpression(NumericExpression* left, NumericExpression* right);
    virtual~DivisionExpression();
    virtual std::string format() const;
    virtual int get_result();

private:
    NumericExpression* left;
    NumericExpression* right;
};
/*
Multiplies left*right.
*/
class MultiplyExpression : public NumericExpression {
public:
    MultiplyExpression(NumericExpression* left, NumericExpression* right);
    virtual~MultiplyExpression();
    virtual std::string format() const;
    virtual int get_result();

private:
    NumericExpression* left;
    NumericExpression* right;
};

#endif
