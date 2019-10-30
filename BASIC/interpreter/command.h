#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "boolean.h"
#include "arithmetic.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class Command{
public:
	virtual ~Command(){}
    virtual std::string format() const = 0;
    virtual std::string command_name(){return "Error";}
    virtual NumericExpression* get_nexp(){
        NumericExpression* j = new Constant(0);
        return j;
    }
    virtual int get_jline(){return -1;}
};
class Empty: public Command{
    virtual ~Empty(){}
    virtual std::string format() const{return "EMPTY";}
    std::string command_name(){return "EMPTY";}

};
class End: public Command{
    virtual ~End(){}
    virtual std::string format() const{return "END";}
    std::string command_name(){return "END";}

};

/*
Print value or expression made 
*/
class Print : public Command {
public:
    Print(NumericExpression*);
    virtual ~Print();
    virtual std::string format() const;
    //int passed in will be -1 if 
     NumericExpression* get_nexp();
    std::string command_name(){return "PRINT";}

private:
    NumericExpression* nexp_; //maybe numeric
};


/*
Let a variable be a specific number
*/
class LetI : public Command {
public:
    LetI(NumericExpression*, NumericExpression*);
    virtual ~LetI();
    virtual std::string format() const;
    std::string command_name(){return "LETI";}


private:
    NumericExpression* var_; //maybe numeric
    NumericExpression* nexp_; //maybe numeric
};
/*
Let an array variable and position be set
*/
class LetA : public Command {
public:
    LetA(NumericExpression*, NumericExpression*);
    virtual ~LetA();
    virtual std::string format() const;
    std::string command_name(){return "LETA";}


private:
    NumericExpression* array_; //maybe numeric
    NumericExpression* nexp_; //maybe numeric

};
/*
Just jumps to a line
*/
class GoTo : public Command {
public:
    GoTo(int);
    virtual ~GoTo();
    virtual std::string format() const;
    std::string command_name(){return "GOTO";}
    virtual int get_jline(){return jline_;}

private:
	int jline_;
};
/*
if a bool expression is true then jump to a line
*/
class IfThen : public Command {
public:
    IfThen(int, BooleanExpression*);
    virtual ~IfThen();
    virtual std::string format() const;
    std::string command_name(){return "IFTHEN";}
    virtual int get_jline(){return jline_;}

private:
	int jline_;
	BooleanExpression* check_;
};

/*
It jumps to a line but it remembers where it came from
*/
class GoSub : public Command  {
public:
    GoSub(int);
    virtual ~GoSub();
    virtual std::string format() const;
    std::string command_name(){return "GOSUB";}
    virtual int get_jline(){return jline_;}


private:
	int jline_;
};
/*
Goes back to the line gosub remembered, if there is none then
it throws an error 
*/
class Return :public Command  {
public:
    virtual ~Return(){}
    virtual std::string format() const;
    std::string command_name(){return "RETURN";}

};

#endif
