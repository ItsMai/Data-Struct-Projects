#include "arithmetic.h"
#include "boolean.h"
#include "command.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <typeinfo>

using namespace std;

map<string, NumericExpression*> int_map;
map<string, map<int, NumericExpression*>> ar_map;

NumericExpression* parse_constant(string line, int &position, int& number){
	bool neg = false;
	string temp = "";
	if(line[position] == '-'){															//if its a negative number check
		neg = true;
		position++;
	}
	while(line[position] != ']' && line[position] != ')' && line[position] != '+' && 
		line[position] != '-' && line[position] != '*' &&line[position] != '/' && position!=(signed)line.size()){
		if(position == (signed)line.size()){
			break;
		}
		temp +=  line[position];
		position++;
	}
	//if it is a negative number then make it to int then neg then new constant
	if(neg){
		int sneeze = stoi(temp);
		sneeze = sneeze *(-1);
		number = sneeze;
		NumericExpression* m  = new Constant(sneeze);
		return m;
	}
	number = stoi(temp);
	NumericExpression* m = new Constant(stoi(temp));
	return m;
}

string parse_variable_name(string line, int &position){
	string var = "";
	while(line[position] != '[' && line[position] != ']' && 
		line[position] != '-' && line[position] != '*' &&line[position] != '/' &&
		line[position] != '(' && line[position] != ')' && line[position] != '+' && position!=(signed)line.size()){
		var += line[position];
		position++;
	}
	return var;
}


BooleanExpression* boolParse(string parse){
	int posin;
	for(unsigned int i = 0; i < parse.size(); i++){
		if (parse[i] == '<' || parse[i] == '>' || parse[i] == '='){
			posin = i;
			break;
		}else{
			posin = 0;
		}
	}
	string left = "";
	string right = "";
	for(int i = 0; i < posin ; i++){
		left += parse[i];
	}
	for(unsigned int i = posin+1; i < parse.size() ; i++){
		right += parse[i];
	}
	char op = parse[posin];
	int o = 0;
	int l_result = 0;
	int r_result = 0;
	NumericExpression* l = nexpParse(left, o, l_result);
	o = 0;
	NumericExpression* r = nexpParse(right, o, r_result);
	 if(op == '<'){
	 	BooleanExpression* m = new LessExpression(l,r);
	 	return m;
	 }else if (op == '>'){
	 	BooleanExpression* m = new GreaterExpression(l,r);
	 	return m;
	 }else if(op == '='){
	 	BooleanExpression* m = new EqualsExpression(l,r);
	 	return m;
	 }else{//error case
	 	BooleanExpression*m = new EqualsExpression(l,r);
	 	return m;
	 }
}

BooleanExpression* boolParse_done(string parse){
	int posin;
	for(unsigned int i = 0; i < parse.size(); i++){
		if (parse[i] == '<' || parse[i] == '>' || parse[i] == '='){
			posin = i;
			break;
		}else{
			posin = 0;
		}
	}
	string left = "";
	string right = "";
	for(int i = 0; i < posin ; i++){
		left += parse[i];
	}
	for(unsigned int i = posin+1; i < parse.size() ; i++){
		right += parse[i];
	}
	char op = parse[posin];
	int o = 0;
	int l_result = 0;
	int r_result = 0;
	NumericExpression* l = nexpParse(left, o, l_result);
	o = 0;
	NumericExpression* r = nexpParse(right, o, r_result);
	NumericExpression* left_done = new Constant(l_result);
	NumericExpression* right_done = new Constant(r_result);
		//warning fix
	l = r;
	r = l;
	 if(op == '<'){
	 	BooleanExpression* m = new LessExpression(left_done,right_done);
	 	return m;
	 }else if (op == '>'){
	 	BooleanExpression* m = new GreaterExpression(left_done,right_done);
	 	return m;
	 }else if(op == '='){
	 	BooleanExpression* m = new EqualsExpression(left_done,right_done);
	 	return m;
	 }else{//error case
	 	BooleanExpression*m = new EqualsExpression(left_done,right_done);
	 	return m;
	 }
}