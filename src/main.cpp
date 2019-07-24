#include <iostream>
#include <fstream>
#include <utility>
#include <list>
#include <sstream>
#include "Lexer.h"
#include "Ast.h"
#include "Parser.h"

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

	std::list <Lexer::Token> tokenList = lexer->run(inputText);
	
	Ast* ast = new Ast();
	Parser* parser = new Parser();
	parser->scan(&tokenList, ast);

	system("pause");
    return 0;
}