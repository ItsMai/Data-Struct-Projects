#include "boolean.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream> 

using namespace std;
/*
==========EQUALS==========
*/
EqualsExpression::EqualsExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}

EqualsExpression::~EqualsExpression() {
    delete this->left;
    delete this->right;
}

string EqualsExpression::format() const {
    return "[" + this->left->format() + " = " + this->right->format() + "]";
}
bool EqualsExpression::get_result(){
	if(this->left->get_val() == this->right->get_val()){
		result_ = true;
		return result_;
	}else{
		result_ = false;
		return false;
	}
}
/*
>>>>>>>>>>GREATER THAN>>>>>>>>>>
*/
GreaterExpression::GreaterExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}

GreaterExpression::~GreaterExpression() {
    delete this->left;
    delete this->right;
}

string GreaterExpression::format() const {
    return "[" + this->right->format() + " < " + this->left->format() + "]";
}
bool GreaterExpression::get_result(){
	if(this->left->get_val() > this->right->get_val()){
		result_ = true;
		return result_;
	}else{
		result_ = false;
		return false;
	}
}
/*
<<<<<<<<<<<LESS THAN<<<<<<<<<
*/
LessExpression::LessExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}

LessExpression::~LessExpression() {
    delete this->left;
    delete this->right;
}

string LessExpression::format() const {
    return "[" + this->left->format() + " < " + this->right->format() + "]";
}
bool LessExpression::get_result(){
	if(this->left->get_val() < this->right->get_val()){
		result_ = true;
		return result_;
	}else{
		result_ = false;
		return false;
	}
}