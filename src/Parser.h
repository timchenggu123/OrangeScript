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

	Ast::Exp* parseExpression(Lexer::Token* token, int startId, int endId);

	Ast::Exp * parseLeft(Lexer::Token * token, int startId);

	Ast::Exp * parseRight(Lexer::Token * token, int endId);

	Ast::Exp* parsePrimaryExpression(Lexer::Token* token);

	void scan(list<Lexer::Token*> *tokens, Ast* ast);

};

#endif