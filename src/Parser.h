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

	Ast* parseExpression(Lexer::Token* token, int startId, int endId);

	Ast::Exp * parseLeft(Lexer::Token * token, int startId);

	Ast::Exp * parseRight(Lexer::Token * token, int endId);

	Ast* run(list<Lexer::Token>* tokens);

private:
	void setUp();	
	OpType* opType;
};

#endif