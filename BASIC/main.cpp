#include <iostream>
#include <fstream>
#include <typeinfo>
#include "interpreter/interpreter.h"

using namespace std;


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide an input file." << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if(input.fail()){
    	cout << "File " << argv[1] << " cannot be opened." << endl;
    	return 1;
    }
    
    Interpreter interpreter(input);
    interpreter.functionality();
    interpreter.write(cout);
    return 0;
}
