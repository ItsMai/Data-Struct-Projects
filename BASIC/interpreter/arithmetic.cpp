#include "arithmetic.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream> 
#include <exception>
#include <stdexcept>
//test typeid() == typeid()
using namespace std;

NumericExpression* NumericExpression::get_array(){
    NumericExpression* empty = new Constant(0);
    return empty;
}

/*
        Constants
*/
Constant::Constant(int value){
	val_ = value;
}
string Constant::format() const {
    return to_string(val_);
}

/*
        Variables 
        ex: x
*/

IntVariable::IntVariable(string name){
	// val_ = value;
	name_ = name;
}
string IntVariable::format() const {
    return this->name_;
}
string IntVariable::get_name(){
    return name_;
}
/*
        Arrays 
        ex: x[9]
*/
ArVariable::ArVariable(string name, NumericExpression* array_): array_(array_){
	// val_ = value;
	name_= name;
}
ArVariable::~ArVariable(){
    delete this->array_;
}

string ArVariable::format() const {

    return this->name_ + "[" + this->array_->format() + "]";
}
string ArVariable::get_name(){
    return name_;
}
NumericExpression* ArVariable::get_array(){
    return array_;
}
/*
++++++++++Addition function+++++++++++++
*/
AdditionExpression::AdditionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}

AdditionExpression::~AdditionExpression() {
    delete this->left;
    delete this->right;
}

string AdditionExpression::format() const {
    return "(" + this->left->format() + " + " + this->right->format() + ")";
}

int AdditionExpression::get_result(){
    val_ = this->left->get_val() + this->right->get_val();
    return val_;
}
/*
----------Subtraction function---------
*/
SubtractionExpression::SubtractionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}
SubtractionExpression::~SubtractionExpression() {
    delete this->left;
    delete this->right;
}

string SubtractionExpression::format() const {
    return "(" + this->left->format() + " - " + this->right->format() + ")";
}
int SubtractionExpression::get_result(){
    val_ = this->left->get_val() - this->right->get_val();
    return val_;
}
/*
//////////Division function//////////
*/
DivisionExpression::DivisionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}

DivisionExpression::~DivisionExpression() {
    delete this->left;
    delete this->right;
}

string DivisionExpression::format() const {
    return "(" + this->left->format() + " / " + this->right->format() + ")";
}

int DivisionExpression::get_result(){
    if(this->right->get_val() == 0){
        string out = " Division by zero: " + this->left->format() + " = " + to_string(this->left->get_val()) +
        ", " + this->right->format() + " = " + to_string(this->right->get_val());
        throw invalid_argument(out);
    }
    val_ = (int)(this->left->get_val() / this->right->get_val());
    return val_;
}
/*
**********Multiplication function**********
*/
MultiplyExpression::MultiplyExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}

MultiplyExpression::~MultiplyExpression() {
    delete this->left;
    delete this->right;
}

string MultiplyExpression::format() const {
    return "(" + this->left->format() + " * " + this->right->format() + ")";
}
int MultiplyExpression::get_result(){
    val_ = this->left->get_val() * this->right->get_val();
    return val_;
}
