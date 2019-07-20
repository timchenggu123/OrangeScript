#include <iostream>
#include "OpType.h"
#include "Parser.h"
#include "Lexer.h"
#include "Ast.h"

Parser::Parser():
	opType(new OpType)
{
}

Parser::~Parser()
{
	delete opType;
}

void Parser::setUp()
{
}

void scan(vector<Lexer::Token> *tokens)
{	
	if (tokens == nullptr) {
		//TODO throw error
		std::cerr << "error at parser schanner" << std::endl;
		exit(1);
	}
	Lexer::Token *token = tokens->begin;
		
	while (token->next != nullptr) 
	{
		if (token->type == Lexer::BREAK) {
			parseStatement(startId, endId, )
		}
	}
}
Ast* Parser::Parser(list<Lexer::Token> tokens) {
	//check type of statement
	//make statement

	//process expressions --use operator precedence parsing https://en.wikipedia.org/wiki/Operator-precedence_parser


	//if to see if properly terminated
}


/*

Ast::Exp* Parser::parseExpressions(Lexer::Token* root) {
	return parseExpression(root, 0);
}

Ast::Exp* Parser::parseExpression(Lexer::Token* lhs, int precedence) {
	Lexer::Token* peek = lhs->next;

	while (OpType::isBinaryOp(peek ->type) &&
		OpType::getPrecedence(peek->type) >= precedence)

}

*/
