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
/*
        Constants
*/
Constant::Constant(int value){
	val_ = value;
}
string Constant::format() const {
    return to_string(val_);
}
int Constant::get_val(){
    return val_;
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
void IntVariable::set(int value){
    val_ = value;
}
int IntVariable::get_val(){
    return val_;
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
void ArVariable::set(int value){
    val_= value;
    
}
int ArVariable::get_val(){
    return val_;
}
string ArVariable::get_name(){
    return name_;
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
    sum_ = this->left->get_val() + this->right->get_val();
    return sum_;
    return 0;
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
    diff_ = this->left->get_val() - this->right->get_val();
    return diff_;
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
    if(this->right->get_val() == 0 && (this->left->get_val() != 0)){
        throw invalid_argument("divided by zero");
    }
    quo_ = (int)(this->left->get_val() / this->right->get_val());
    cerr << quo_ << endl;
    return quo_;
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
    prod_ = this->left->get_val() * this->right->get_val();
    return prod_;
}
