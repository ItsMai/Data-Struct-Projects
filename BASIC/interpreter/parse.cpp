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

NumericExpression* nexpParse(string toParse, int &position, int &result){
	if(isdigit(toParse[position]) || toParse[position] == '-'){ 						//constant case
		int number = 0;
		NumericExpression *constant_parsed = parse_constant(toParse, position, number);
		if(result == 0){																//checking if nothing has been pared yet
			result = number;
		}
		return constant_parsed;
	}else if(isalpha(toParse[position])){
		string variableName = parse_variable_name(toParse,position);
		if(toParse[position] != '['){													//after getting the name, its a variable
			NumericExpression* int_var = new IntVariable(variableName);
			if(result == 0){
				result = int_var->get_val();
				cerr << result << endl;
			}
			return int_var;
		}else{
			position++;																	//skipping over [
			NumericExpression* ix = nexpParse(toParse,position, result);
			position++;																	//skipping over ]
			return new ArVariable(variableName, ix);
		}
	}else{ 																				//binary operator -+/*
		position++;
		NumericExpression* left = nexpParse(toParse, position, result);
		char op = toParse[position];
		position++;
		NumericExpression* right = nexpParse(toParse, position, result);
		position++;

		if(op == '+'){
			NumericExpression* prettyp = new AdditionExpression(left,right);
			result = prettyp->get_result();
			return prettyp;
		}else if(op == '-'){
			NumericExpression* prettyp = new SubtractionExpression(left,right);
			result = prettyp->get_result();
			return prettyp;
		}else if(op == '*'){
			NumericExpression* prettyp = new MultiplyExpression(left,right);
			result = prettyp->get_result();
			return prettyp;
		}else if(op == '/'){
			NumericExpression* prettyp = new DivisionExpression(left,right);
			result = prettyp->get_result();
			return prettyp;
		}else{
			NumericExpression* prettyp = new DivisionExpression(left,right);
			return prettyp;
		}
	}
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

