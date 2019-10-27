#include "command.h"
#include "boolean.h"
#include "arithmetic.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
/*
==========PRINT==========
*/
Print::Print(NumericExpression* nexp_): nexp_(nexp_){
}
Print::~Print(){
	delete this->nexp_;
}
string Print::format () const{
	return "PRINT " + this->nexp_->format();
}
void Print::print_(){
	cout << nexp_->get_val();
}
/*
==========LET VARIABLE==========
*/
LetI::LetI(NumericExpression* var_, NumericExpression* nexp_): var_(var_), nexp_(nexp_){
}
LetI::~LetI(){
	delete this->nexp_;
	delete this->var_;
}
string LetI::format () const{
	return "LET " + this->var_->format() + " " + this->nexp_->format(); 
}
void LetI::let_var(int value){
	
}
/*
==========LET ARRAY==========
*/
LetA::LetA(NumericExpression* array_, NumericExpression* nexp_): array_(array_), nexp_(nexp_){
}
LetA::~LetA(){
	delete this->nexp_;
	delete this->array_;
}

string LetA::format () const{
	return "LET " + this->array_->format() + " " +this->nexp_->format(); 
}
/*
==========GOTO==========
*/
GoTo::GoTo(int* jline_): jline_(jline_){
}
GoTo::~GoTo(){
	delete this->jline_;
}

string GoTo::format()const{
	string jumpstring = to_string(*jline_);
	return "GOTO <" + jumpstring + ">";
}
/*
==========IF THEN==========
*/
IfThen::IfThen(int* jline, BooleanExpression* check){

	this->jline_ = jline;
	this->check_ = check;
}
IfThen::~IfThen(){
	delete this->jline_;
	delete this->check_;
}

string IfThen::format()const{
	return "IF " + this->check_->format() + " THEN <" + to_string(*jline_) + ">";
}
/*
==========GOSUB==========
*/
GoSub::GoSub(int* jline, int* prev){
	this->jline_=jline; 
	this->prev_ =prev;
}
GoSub::~GoSub(){
	delete this->jline_;
	delete this->prev_;
}

string GoSub::format()const{
	return "GOSUB <" + to_string(*jline_) + ">";
}

/*
==========RETURN==========
*/
string Retur::format()const{
	return "RETURN";
}