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
#include <iterator>


using namespace std;

Interpreter::Interpreter(istream& in) {
    this->parse(in);
}

NumericExpression* Interpreter::parse_constant(string line, int &position){
    bool neg = false;
    string temp = "";
    if(line[position] == '-'){                                                          //if its a negative number check
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

NumericExpression* Interpreter::nexpParse(string toParse, int &position){
    if(isdigit(toParse[position]) || toParse[position] == '-'){                         //constant case
        NumericExpression *constant_parsed = parse_constant(toParse, position);
        return constant_parsed;
    }else if(isalpha(toParse[position])){
        string variableName = parse_variable_name(toParse,position);
        bool found = false;
        if(toParse[position] != '['){                                                   //after getting the name, its a variable
            NumericExpression* int_var = new IntVariable(variableName);
            if(int_variables.find(variableName)!= int_variables.end()){
                found = true;
            }
            if(found){
                int_var->set(int_variables[variableName]->get_val());
            }
            return int_var;
        }else{
            position++;                                                                 //skipping over [
            NumericExpression* ix = nexpParse(toParse,position);
            NumericExpression* ar_var = new ArVariable(variableName, ix);
            if(array_variables.find(variableName) != array_variables.end()){
                if(array_variables.at(variableName).find(ix->get_val()) != array_variables.at(variableName).end()){
                    found = true;
                }
            }
            if(found){
                ar_var->set(array_variables[variableName][ix->get_val()]->get_val());
            }
            position++;                                                                 //skipping over ]
            return ar_var;
        }
    }else{                                                                              //binary operator -+/*
        position++;
        NumericExpression* left = nexpParse(toParse, position);
        char op = toParse[position];
        position++;
        NumericExpression* right = nexpParse(toParse, position);
        position++;
        NumericExpression* prettyp;
        if(op == '+'){
            prettyp = new AdditionExpression(left,right);
        }else if(op == '-'){
            prettyp = new SubtractionExpression(left,right);
        }else if(op == '*'){
            prettyp = new MultiplyExpression(left,right);
        }else if(op == '/'){
            prettyp = new DivisionExpression(left,right);
        }else{

        }
        //if(done){
            try{
                prettyp->set(prettyp->get_result());

            }
            catch(exception& e){
                error_string = e.what();
                error_line = current_line_error;
            }
        //}
        

        return prettyp;
    }
}

BooleanExpression* Interpreter::boolParse(string parse){
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

void Interpreter::parse_if(string line){
    string command_name;
    string line_number;
    stringstream stream(line);
    stream >> line_number;
    stream >> command_name;
    string temp;
    string restString = "";
    while(stream >> temp){
        restString += temp;
    }  

    int posi = 0;                                                           //position found where is the then begins
    for(unsigned int i = 0; i < restString.size() - 3 ; i++){               //Checking where the THEN is 
        if(restString[i] == 'T' && restString[i+1] == 'H'  && restString[i+2] == 'E' && restString[i+3] == 'N'  ){
            posi = i;
            break;
        } 
    }
    string boo = "";
    for(int i = 0; i < posi ; i++ ){
        boo+= restString[i];
    }
    string jline = "";
    for(unsigned int i = posi+4; i < restString.size(); i++){
        jline += restString[i];
    }                                                                       //getting the line to jump to 
    //if the format was input
    for(unsigned int i = 0; i < jline.size(); i++){
        if(jline[i] == '<' || jline[i] == '>'){
            jline.erase(jline.begin()+i);
        }
    }
    for(unsigned int i = 0; i < boo.size(); i++){
        if(boo[i] == '[' || boo[i] == ']'){
            boo.erase(boo.begin()+i);
        }
    }
    int jump = stoi(jline);
    //pretty printing
    int lineNum = stoi(line_number);
    BooleanExpression* bexp = boolParse(boo);
    Command* if_then = new IfThen(jump, bexp);
    if(!done){
        out_lines.push_back(line_number + " " + if_then->format());
    }
    //functionality
    map<int,Command*>::iterator it = line_command.find(lineNum);
    if(it != line_command.end()){
        line_command.erase(it);
        line_command[lineNum] = if_then;
    }else{
        line_command[lineNum] = if_then;
    }
}

void Interpreter::parse_let(string line){
    int o =0;                                                                               // passing an int to be by reference
    string command_name;
    bool array = false;
    string line_number;
    string temp;
    stringstream stream(line);
    stream >> line_number;
    stream >> command_name;
    string variable;
    stream >> variable;
    bool namebrack = false;
    int posin;                                                                  //position
    for(unsigned int i =0; i < variable.size(); i++){                           //test case  x[ 90....
        if(variable[i] == '['){
            array = true;
            namebrack = true;                                                   // test case x[ 0000...  x[8+3]
            posin = i;
            break;
        }
    }
    if(!array){
        stream >> temp;
        if(temp[0] == '['){                                                     //test x [90....
            array = true;
        }else{                                                                  //we know its a variable for sure 
            string rest = temp;                                                 //test case x 8
            while(stream >> temp){
                rest += temp;
            }
            o = 0;
            NumericExpression* nexp = nexpParse(rest, o);                       //parse for arguemnt for value
            NumericExpression* varname = new IntVariable(variable);             //the var name is set to an int variable
            //pretty printing
            Command* pretty_var = new LetI(varname, nexp);
            if(done){
                varname->set(nexp->get_val());
                map<string,NumericExpression*>::iterator intit = int_variables.find(variable);
                if(intit != int_variables.end()){
                    int_variables.erase(intit);
                    int_variables[variable] = varname;
                }else{
                    int_variables[variable] = varname;
                }
            }else{
                out_lines.push_back(line_number + " " + pretty_var->format());
            }
            map<int,Command*>::iterator it = line_command.find(stoi(line_number));
            if(it != line_command.end()){
                line_command.erase(it);
                line_command[stoi(line_number)] = pretty_var;
            }else{
                line_command[stoi(line_number)] = pretty_var;
            }
        }
    }
    if(array){/////////////////////work for an array
        string tempin = "";                                                     //p
        string next = "";                                                       //the next after the space
        if(namebrack){                                                          //case: x[ or x[0]
            if(variable[variable.size()-1] == posin){
                next = '[';                                                     //just containing the variable name now
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
        }else{                                                                  //case : x [9]
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
        for(unsigned int i = 1; i < temp.size(); i ++){                         //get rid of open bracket at the beginning
            next += temp[i];
        }
        int check_open = -1;
        for(unsigned int i = 0; i < next.size(); i++){
            if(next[i] == '['){
                check_open = i;
                break;
            }
        }
        string ix = "";                                                         //index
        NumericExpression* index;
        int ix_string = 0;                                                      //position where the rest of the let is
        if(check_open != -1){
            int open_bracket_amount = 1;
            for(unsigned int i = 0; i < next.size(); i++){                      //get rid of open bracket at the beginning
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
            index = nexpParse(inside_brackets,o);                   //parse what is inside the brackets
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
        for(unsigned int i = ix_string+1 ; i < next.size();i++){                //gets the rest of the string to go in the variable

            nexp += next[i];
        }
        o = 0;
        //pretty print     
        NumericExpression* exp = nexpParse(nexp, o);     
        NumericExpression* ary = new ArVariable(variable, index);               //new array
        Command* let = new LetA(ary, exp);                                      //new let command for pretty printing
        out_lines.push_back(line_number + " " + let->format());
        //functionality
        if(done){
            if(array_variables.find(variable) != array_variables.end()){
                if(array_variables.at(variable).find(index->get_val()) != array_variables.at(variable).end()){
                    array_variables.at(variable).erase(array_variables.at(variable).find(index->get_val()));
                    array_variables[variable][index->get_val()] = exp;                      //setting it in the map
                    array_variables[variable][index->get_val()]->set(exp->get_val());       //setting the valu inside
                }
            }else{
                array_variables[variable][index->get_val()] = exp;                      //setting it in the map
                array_variables[variable][index->get_val()]->set(exp->get_val());       //setting the valu inside
            }
        }
        
        map<int,Command*>::iterator it = line_command.find(stoi(line_number));
        if(it != line_command.end()){
            line_command.erase(it);
            line_command[stoi(line_number)] = let;
        }else{
            line_command[stoi(line_number)] = let;
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
    string temp;
    while (getline(in, line)) {
    	string after_command = "";															//line for everything but command and line number
        stringstream stream(line);
        stream >> line_number;
        stream >> command_name;
        current_line_error = stoi(line_number);
        if(command_name == "END"){
        	Command* it_end = new End;
        	line_command[stoi(line_number)] = it_end;
        	out_lines.push_back( line_number + " " + command_name);
        }else if(command_name == "LET"){
            parse_let(line);
        	
        }else if(command_name == "PRINT"){  
            string temp;
            string restString = "";
            while(stream >> temp){
                restString += temp;
            }  
            o = 0;
            //pretty print
            NumericExpression* nexp = nexpParse(restString, o);
            Command * print = new Print(nexp);
            out_lines.push_back(line_number + " " + print->format());
            //functionality
            line_command[stoi(line_number)] = print;
        }else if(command_name == "IF"){    	
                parse_if(line);
        }else if(command_name == "GOSUB"){
        	string temp;
        	int jline;
        	stream >> temp;
        	jline = stoi(temp); 														//read in the number line to jump to 
        	Command *gosub = new GoSub(jline); 
        	out_lines.push_back(line_number + " " + (gosub->format())); 				//push it into the vector of lines
        	line_command[stoi(line_number)] = gosub;
        }else if(command_name == "GOTO"){
        	string temp;
        	int jline;
        	stream >> temp;
        	jline = stoi(temp); 														//read in the number line to jump to 
        	Command* go_to = new GoTo(jline);
            //pretty print
        	out_lines.push_back(line_number + " " + (go_to->format())); 				//push it into the vector of lines
            //functionality
        	line_command[stoi(line_number)] = go_to;
       	}else if(command_name == "RETURN"){
            //pretty printing
        	out_lines.push_back(line_number + " RETURN");
            //functionality
        	Command* ret = new Return; 
        	line_command[stoi(line_number)] = ret;
        }
	}
    done = true;
}

void Interpreter::write(ostream& out) {
	// cerr <<"if the type id works for bool and numeric: " << (typeid(bool) == typeid(array))<< endl;
	for(unsigned int i = 0; i < out_lines.size(); i++){
		out << out_lines[i] << endl;
	} 
}

void Interpreter::functionality(){
    map<int, Command*>::iterator it;
    for(it = line_command.begin(); it != line_command.end();){
        if(it->first == error_line){
            cout << "Error in line " << error_line << ": " << error_string << endl;
            return;
        }
        if(it->second->command_name() == "PRINT"){                  //Prints out the NUMERIC expression, newline after
            NumericExpression* printing =  it->second->get_nexp();
            if(printing->is_array() == -1){ //variable
                string name = printing->get_name();
                map<string, NumericExpression*>::iterator finding = int_variables.find(name);
                cout << finding->second->get_val() << "\n";
            }else if(printing->is_array() == 1){ //array
                string name = printing->get_name();
                NumericExpression* index = printing->get_array();
                NumericExpression* finding = array_variables[name][index->get_val()];
                cout << finding->get_val()<< endl;
            }else{
                cout << it->second->get_nexp()->get_val() << "\n";
            }
        }else if(it->second->command_name() == "LETA"){
            int line = it->first; 
            string let_string = to_string(line) + " " + it->second->format();
            parse_let(let_string);
        }else if(it->second->command_name() == "LETI"){
            int line = it->first; 
            string let_string = to_string(line) + " " + it->second->format();
            parse_let(let_string);
        }else if(it->second->command_name() == "GOTO"){
            if(line_command.find(it->second->get_jline()) == line_command.end() ){                    //jline does not exist
                cout <<  "Error in line "<< it->first << ": GOTO non-existent line <" << it->second->get_jline() << ">.\n";
                return;
            }
            it = line_command.find(it->second->get_jline());
            continue;
            //jump line
        }else if(it->second->command_name() == "IFTHEN"){
            int line = it->first; 
            string let_string = to_string(line) + " " + it->second->format();
            parse_if(let_string);

            if(line_command.find(it->second->get_jline()) == line_command.end() ){                    //jline does not exist
                cout << "Error in line "<< it->first << ": IF jump to non-existent line <" << it->second->get_jline() << ">.\n";
                return;
            }
            if(it->second->get_check()->get_result()){                                                 //only do if bool is true
                it = line_command.find(it->second->get_jline());
                continue;
            }
        }else if(it->second->command_name() == "GOSUB"){
            if(line_command.find(it->second->get_jline()) == line_command.end() ){                    //jline does not exist
                cout << "Error in line "<< it->first << ": GOSUB non-existent line <" << it->second->get_jline() << ">.\n";
                return;
            }
            lines_remembered.push(it->first);
            it = line_command.find(it->second->get_jline());
            continue;
        }else if(it->second->command_name() == "RETURN"){
            if(lines_remembered.empty()){
                cout << "Error in line "<< it->first << ": No matching GOSUB for RETURN.\n";
                return;
            }
            //jumpline in stack
            int jump = lines_remembered.top();
            lines_remembered.pop();
            it = line_command.find(jump);
            it++;
            continue;
        }else if(it->second->command_name() == "END"){
            return;
        }
        it++;
    }
}