#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include "Ast.h"
#include "OpType.h"
#include "FunRegistry.h"
#include <list>
class Parser {
public:
	Parser();
	~Parser();

	Ast::Exp* parseExpression(Lexer::Token* token_start, Lexer::Token* token_end);
	std::list<Ast::Exp*>* parseDelimitedExpressions(Lexer::Token* token_start, Lexer::Token* token_end);
	Ast::Exp* parsePrimaryExpression(Lexer::Token* token);

	void parse(list<Lexer::Token*> *tokens, Ast* ast, FunRegistry* fun_registry);

private: 
};

#endif