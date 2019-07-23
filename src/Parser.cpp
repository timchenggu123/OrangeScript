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

void scan(vector<Lexer::Token> *tokens, Ast* ast)
{	
	if (tokens == nullptr) {
		//TODO throw error
		std::cerr << "error at parser schanner" << std::endl;
		exit(1);
	}
	list<Exp*> args;
	Ast::Exp* rootNode = Ast::makeCodeBlock(&args);
	
	Lexer::Token *token = tokens->begin;
	int startId = 0;
	int endId = 0;
	while (token->next != nullptr) 
	{
		if (token->type == Lexer::BREAK) {
			if (startId == endId) {
				token = token->next;
				continue;
			}
			rootNode->arguments->push_back(parseExpression(token, startId, endId));
			token = token->next;
			startId = token.id;
			endId = token.id;
			continue;
		}
	 	token = token->next;
		endId = token->id;
	}
	ast->setRoot(rootNode);
}

Ast* Parser::parseExpression(Lexer::Token* token, int startId, int endId) {
	Ast* ast = new Ast();
	int min_precedence = INFINITY;
	int base_precedence = 0;
	int expType = 0;
	Lexer::Token* pivot;
	while (token->id != endId) {
		token = token->prev;
		if (OpType::isBinaryOp(token->type) &&
			OpType::getPrecedence(token ->type) < min_precedence){
			min_precedence = OpType::getPrecedence(token->type);
			pivot = token;
			expType = Ast::BINARY;
		}
	}
	if (expType == 0) {
		//Expected an expression; throw an error here.
	}
	if (expType == Ast::BINARY) {
		ast->setRoot(Ast::makeBinaryExp(pivot->type,
			parseLeft(pivot, startId), parseRight(pivot, endId);
	}
	//parse unary expression
	return ast;
}

Ast::Exp* Parser::parseLeft(Lexer::Token* token, int startId) {
	int min_precedence = INFINITY;
	int endId = token->id;
	int base_precedence = 0;
	int expType = 0;
	Lexer::Token* pivot;
	while (true) {
		token = token->prev;
		if (OpType::isBinaryOp(token->type) &&
			OpType::getPrecedence(token->type) < min_precedence) {
			min_precedence = OpType::getPrecedence(token->type);
			pivot = token;
			expType = Ast::BINARY;
		}

		if (token->id == startId) {
			//We do not put the condition in the while 
			//statement because startId is incluisve.
			break;
		}
	}
	if (expType == 0) {
		//Expected an expression; throw an error here.
	}
	if (expType == Ast::BINARY) {
		return parseLeft(pivot, startId), parseRight(pivot, endId);
	}
	//parse unary expression
}

Ast::Exp* Parser::parseRight(Lexer::Token* token, int endId) {
	int min_precedence = INFINITY;
	int startId = token->id;
	int base_precedence = 0;
	int expType = 0;
	Lexer::Token* pivot;
	while (token->id == endId) {
		token = token->next;
		if (OpType::isBinaryOp(token->type) &&
			OpType::getPrecedence(token->type) < min_precedence) {
			min_precedence = OpType::getPrecedence(token->type);
			pivot = token;
			expType = Ast::BINARY;
		}
	}
	if (expType == 0) {
		//Expected an expression; throw an error here.
	}
	if (expType == Ast::BINARY) {
		return parseLeft(pivot, startId), parseRight(pivot, endId);
	}
	//parse unary expression

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
