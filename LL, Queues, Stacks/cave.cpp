#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>

using namespace std;

int cave(string s){
	stack<char>p;
	char temp;
	for(unsigned int i = 0; i < s.size(); i++){
		if(p.empty()){
			p.push(s[i]); //nothing in the stack
		}else if(s[i] == 'N'){
			temp = p.top();
			if(temp == 'S'){
				p.pop();
			}else{
				p.push(s[i]);
			}
		}else if(s[i] == 'S'){
			temp = p.top();
			if(temp == 'N'){
				p.pop();
			}else{
				p.push(s[i]);
			}
		}else if(s[i] == 'W'){
			temp = p.top();
			if(temp == 'E'){
				p.pop();
			}else{
				p.push(s[i]);
			}
		}else if(s[i] == 'E'){
			temp = p.top();
			if(temp == 'W'){
				p.pop();
			}else{
				p.push(s[i]);
			}
		}
	}
	return p.size();
}

int main(int argc, char* arg[]){
	if(argc< 2){
		cerr << "Please provide an input file." << endl;
		return 1;
	}
	ifstream input;
	input.open(arg[1]);
	if(input.fail()){ cout << "Unable to open file" <<endl;}
	string line;
	string dir = "";
	string temp;
	while(getline(input, line)){
		stringstream stream(line);
		while(stream >> temp){
			dir+= temp;
		}
	}
	cout << "The end result is: " << cave(dir) << endl;
	return 0;


}