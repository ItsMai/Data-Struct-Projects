#include "interpreter.h"
#include "boolean.h"
#include "arithmetic.h"
#include "command.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <typeinfo>

using namespace std;

Interpreter::Interpreter(istream& in) {
    this->parse(in);
}

NumericExpression* Interpreter::parse_constant(string line, int &position){
	bool neg = false;
	string temp = "";
	//if its a negative number check
	if(line[position] == '-'){
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
		NumericExpression* m  = new Constant(sneeze);
		return m;
	}
	NumericExpression* m = new Constant(stoi(temp));
	return m;
}

string Interpreter::parse_variable_name(string line, int &position){
	string var = "";
	while(line[position] != '[' && line[position] != ']' && 
		line[position] != '-' && line[position] != '*' &&line[position] != '/' &&
		line[position] != '(' && line[position] != ')' && line[position] != '+' && position!=(signed)line.size()){
		var += line[position];
		position++;
	}
	return var;
}

BooleanExpression* Interpreter::boolParse(string parse){
	int posin;
	for(unsigned int i = 0; i < parse.size(); i++){
		if (parse[i] == '<' || parse[i] == '>' || parse[i] == '='){
			posin = i;
			break;
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
	NumericExpression* l = nexpParse(left, o);
	o = 0;
	NumericExpression* r = nexpParse(right, o);
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

NumericExpression* Interpreter::nexpParse(string toParse, int &position){
	if(isdigit(toParse[position]) || toParse[position] == '-'){ 						//constant case
		return parse_constant(toParse, position);
	}else if(isalpha(toParse[position])){
		string variableName = parse_variable_name(toParse,position);
		if(toParse[position] != '['){													//after getting the name, its a variable
			return new IntVariable(variableName);
		}else{
			position++;																	//skipping over [
			NumericExpression* ix = nexpParse(toParse,position);
			position++;																	//skipping over ]
			return new ArVariable(variableName, ix);
		}
	}else{ 																				//binary operator -+/*
		position++;
		NumericExpression* left = nexpParse(toParse, position);
		char op = toParse[position];
		position++;
		NumericExpression* right = nexpParse(toParse, position);
		position++;
		if(op == '+'){
			return new AdditionExpression(left,right);
		}else if(op == '-'){
			return new SubtractionExpression(left,right);
		}else if(op == '*'){
			return new MultiplyExpression(left,right);
		}else if(op == '/'){
			return new DivisionExpression(left,right);
		}else{
			return new DivisionExpression(left,right);
		}
	}
}

void Interpreter::parse(istream& in) {
	int o =0;																				// passing an int to be by reference
    string line;
    string command_name;
    string pparse;																			//reading in 
    string firststrim;
    string line_number;
   	bool array = false;
    string temp;
    while (getline(in, line)) {
    	string after_command = "";															//line for everything but command and line number
        stringstream stream(line);
        stream >> line_number;
        if(!(stream >> command_name)){														//if line and has no command
        	Command* empty = new Empty;

        	line_command[stoi(line_number)] = empty;
        	out_lines.push_back(line_number);
        	continue;
        }
        if(command_name == "END"){
        	Command* it_end = new End;
        	line_command[stoi(line_number)] = it_end;
        	out_lines.push_back( line_number + " " + command_name);
        }else if(command_name == "LET"){
        	string variable;
        	stream >> variable;
        	array = false;
        	bool namebrack = false;
        	int posin; 																	//position
        	for(unsigned int i =0; i < variable.size(); i++){							//test case  x[ 90....
        		if(variable[i] == '['){
        			array = true;
        			namebrack = true;													// test case x[ 0000...  x[8+3]
        			posin = i;
        			break;
        		}
        	}
        	if(!array){
        		stream >> temp;
        		if(temp[0] == '['){														//test x [90....
        			array = true;
        		}else{																	//we know its a variable for sure 
        			string rest = temp;													//test case x 8
        			while(stream >> temp){
        				rest += temp;
        			}
        			o = 0;
        			NumericExpression* nexp = nexpParse(rest, o);						//parse for arguemnt for value
        			NumericExpression* varname = new IntVariable(variable);				//the var name is set to an int variable
        			Command*m = new LetI(varname, nexp);
        			out_lines.push_back(line_number + " " + m->format());
        		}
        	}
        	if(array){/////////////////////work for an array
        		string tempin = "";														//p
        		string next = ""; 														//the next after the space
        		if(namebrack){ 															//case: x[ or x[0]
        			if(variable[variable.size()-1] == posin){
        				next = '[';														//just containing the variable name now
        			}else{
        				for(unsigned int i = posin; i < variable.size(); i++){
        					tempin += variable[i];
        				}
        				for(unsigned int i = 0; i < tempin.size();i++){
        					next += tempin[i];
        				}
        				string tempname = "";
        				for(int i = 0;i < posin ;i++){
        					tempname += variable[i];
        				}
        				variable = tempname;
        			}
        			while(stream >>tempin){
        				next +=tempin;
        			}
        		}else{																	//case : x [9]
        			string nospace = "";
        			for(unsigned int i = 0;i < temp.size()-1; i++){
        				nospace += temp[i+1];
        			}
        			while(stream >> temp){
        				nospace += temp;
        			}
        			next = nospace;
        		}
        		string temp = next;
        		next = "";
        		for(unsigned int i = 1; i < temp.size(); i ++){ 						//get rid of open bracket at the beginning
        			next += temp[i];
        		}
        		int check_open = -1;
        		for(unsigned int i = 0; i < next.size(); i++){
        			if(next[i] == '['){
        				check_open = i;
        				break;
        			}
        		}
        		string ix = "";															//index
        		NumericExpression* index;
        		int ix_string = 0;														//position where the rest of the let is
        		if(check_open != -1){
        			int open_bracket_amount = 1;
        			for(unsigned int i = 0; i < next.size(); i++){						//get rid of open bracket at the beginning
        				if(next[i] == '['){
        					open_bracket_amount++;
        				}else if(next[i] == ']'){
        					open_bracket_amount--;
        				}
        				if(open_bracket_amount <= 0){
        					ix_string = i;
        					break;
        				}
        			}
        			string inside_brackets = "";
      				for(int i = 0; i < ix_string;i++){
      					inside_brackets += next[i];
      				}
        			o = 0;
        			index = nexpParse(inside_brackets,o);								//parse what is inside the brackets
        		}else{
	        		for(int i = 0; i < (signed) next.size(); i++){
		       			if(next[i] == ']'){
		        			ix_string = i;
		        			break;
		        		}
		       		}	
			       	for(int i = 0; i < ix_string; i++){
	        			ix += next[i];
	        		}
	        		o = 0;
	        		index = nexpParse(ix, o);
        		}
        		string nexp = "";
        		for(unsigned int i = ix_string+1 ; i < next.size();i++){	        	//gets the rest of the string to go in the variable

        			nexp += next[i];
        		}
        		o = 0;
        		NumericExpression* exp = nexpParse(nexp, o);
        		NumericExpression* ary = new ArVariable(variable, index);				//new array
        		Command* let = new LetA(ary, exp);											//new let command
        		line_command[stoi(line_number)] = let;
    			out_lines.push_back(line_number + " " + let->format());
        	}
        }else if(command_name == "PRINT" || command_name == "IF"){
        	string temp;
        	string restString = "";
        	while(stream >> temp){
        		restString += temp;
        	}        	

        	if(command_name == "PRINT"){
        		o = 0;
       			NumericExpression* nexp = nexpParse(restString, o);
       			Command *print = new Print(nexp);
       			line_command[stoi(line_number)] = print;
       			out_lines.push_back(line_number + " " + print->format());
        	}else if(command_name == "IF"){
        		int posi = 0;															//position found where is the then begins
        		for(unsigned int i = 0; i < restString.size() - 3 ; i++){ 				//Checking where the THEN is 
        			if(restString[i] == 'T' && restString[i+1] == 'H'  && restString[i+2] == 'E' && restString[i+3] == 'N'  ){
        				posi = i;
        				break;
        			} 
        		}
        		string boo = "";
        		for(int i = 0; i < posi ; i++ ){
        			boo+= restString[i];
        		}
        		o = 0;
        		BooleanExpression* bexp = boolParse(boo);
        		string jline = "";
        		for(unsigned int i = posi+4; i < restString.size(); i++){
        			jline += restString[i];
        		}																		//getting the line to jump to 
        		int jump = stoi(jline);
        		Command* if_then = new IfThen(&jump, bexp);
        		line_command[stoi(line_number)] = if_then;
        		out_lines.push_back(line_number + " " + if_then->format());
        	}
        }else if(command_name == "GOSUB"){
        	string temp;
        	int jline;
        	stream >> temp;
        	jline = stoi(temp); 														//read in the number line to jump to 
        	int line_num = stoi(line_number);
        	Command *gosub = new GoSub(&jline, &line_num); 
        	out_lines.push_back(line_number + " " + (gosub->format())); 				//push it into the vector of lines
        	line_command[stoi(line_number)] = gosub;
        }else if(command_name == "GOTO"){
        	string temp;
        	int jline;
        	stream >> temp;
        	jline = stoi(temp); 														//read in the number line to jump to 
        	Command* go_to = new GoTo(&jline);
        	out_lines.push_back(line_number + " " + (go_to->format())); 					//push it into the vector of lines
        	line_command[stoi(line_number)] = go_to;
       	}else if(command_name == "RETURN"){
        	out_lines.push_back(line_number + " RETURN");
        	Command* ret = new Retur; 
        	line_command[stoi(line_number)] = ret;
        	
        }
    	
	}
}

void Interpreter::write(ostream& out) {
	// cerr <<"if the type id works for bool and numeric: " << (typeid(bool) == typeid(array))<< endl;
	for(unsigned int i = 0; i < out_lines.size(); i++){
		out << out_lines[i] << endl;
	} 
}