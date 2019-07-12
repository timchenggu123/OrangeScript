#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include "Ast.h"
#include <list>
class Parser {
public:
	Parser();
	~Parser();

	Ast* run(list<Lexer::Token>* tokens)

private:
	void setUp();	
};

#endif