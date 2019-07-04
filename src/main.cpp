#include <iostream>
#include <fstream>
#include <utility>
#include <list>
#include <sstream>
#include "..\h\Lexer.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::stringstream;
int main (int argc, char *argv[]){

	if (argc == 0) {
		cout << "Error: no input file detected";
		exit(1);
	}
	string inputFileName = argv[1];
	ifstream inputFile;
	
	//try opening the input file
	inputFile.open(inputFileName);
	if (!inputFile) {
		std::cerr << "Error: Input file cannot be opened" << endl;
		exit(1);
	}

	stringstream buffer;
	buffer << inputFile.rdbuf();
	string inputText(buffer.str());
	inputFile.close();

	cout << endl;

	Lexer* lexer = new Lexer();

	std::list < std::pair<int, string>> tokenList = lexer->run(inputText);
	

	system("pause");
    return 0;
}