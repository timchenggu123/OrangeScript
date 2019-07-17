#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include "Ast.h"
#include "OpType.h"

#include <list>
class Parser {
public:
	Parser();
	~Parser();

	Ast::Exp * parseExpressions(Lexer::Token * root);

	Ast::Exp * parseExpression(Lexer::Token * lhs, int precedence);

	Ast* run(list<Lexer::Token>* tokens)

private:
	void setUp();	
	OpType* opType;
};

#endif