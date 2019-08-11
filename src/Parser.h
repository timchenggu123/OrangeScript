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

	Ast::Exp* parseExpression(Lexer::Token* token_end, Lexer::Token* token_start);

	Ast::Exp* parsePrimaryExpression(Lexer::Token* token);

	void scan(list<Lexer::Token*> *tokens, Ast* ast);

};

#endif