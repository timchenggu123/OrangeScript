#include <iostream>
#include <sstream>
#include "OpType.h"
#include "Parser.h"
#include "Lexer.h"
#include "Ast.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}


void Parser::scan(list<Lexer::Token*> *tokens, Ast* ast)
{	
	if (tokens == nullptr) {
		//TODO throw error
		std::cerr << "error at parser schanner" << std::endl;
		exit(1);
	}
	list<Ast::Exp*>*args = new list<Ast::Exp*>;
	Ast::Exp* rootNode = Ast::makeCodeBlock(args);
	
	Lexer::Token *token = tokens->front();
	int startId = 0;
	int endId = 0;
	while (token != nullptr) 
	{
		endId = token->id;

		if (token->type == Lexer::BREAK) {
			if (startId == endId) {
				token = token->next;
				continue;
			}
			rootNode->arguments->push_back(parseExpression(token, startId, endId));
			startId = token->id;
			token = token->next;
			continue;

		}
	 	token = token->next;
	}
	ast->setRoot(rootNode);
}

Ast::Exp* Parser::parseExpression(Lexer::Token* token, int startId, int endId) {
	int min_precedence = 0; //using a large number right now...could try infinity
	int base_precedence = 0;
	int expType = 0;
	Lexer::Token* pivot;
	while (token ->prev != nullptr &&
		token->prev->id != startId) {
		token = token->prev;
		if (token->type == Lexer::OPERATOR) {
			if (OpType::isBinaryOp(token->opType) &&
				OpType::getPrecedence(token->opType) > min_precedence) {
				min_precedence = OpType::getPrecedence(token->opType);
				pivot = token;
				expType = Ast::BINARY;
			}
		}
		else {
			continue;
		}

	}
	if (expType == 0) {
		std::cerr << "expected expression at ln:" << token->ln << " col " << token->col;
	}
	if (expType == Ast::BINARY) {
			Ast::Exp* watch = Ast::makeBinaryExp(
				pivot->opType,parseLeft(pivot, startId), parseRight(pivot, endId));
			return watch;
	}
	//parse unary expression
	return nullptr;
}

Ast::Exp* Parser::parseLeft(Lexer::Token* token, int startId) {
	int endId = token->id;
	//we parse from endId to startId right to left.
	//both token with endId and startId are excluded from parsing

	int min_precedence = 0;
	int base_precedence = 0;
	int expType = 0;

	if (endId - startId == 2) {
		//If there is only one token included,
		//we parse it as a primary expression.
		Ast::Exp* watch = parsePrimaryExpression(token->prev);
		return watch;
	}

	Lexer::Token* pivot;

	//search for operator with the highest precedence. 
	while (token->prev != nullptr &&
		token->prev->id != startId) {
		token = token->prev;
		if (token->type == Lexer::OPERATOR) {
			if (OpType::isBinaryOp(token->opType) &&
				OpType::getPrecedence(token->opType) > min_precedence) {
				min_precedence = OpType::getPrecedence(token->opType);
				pivot = token;
				expType = Ast::BINARY;
				token = token->prev;
			}
		}
	
	}
	if (expType == 0) {
		//Expected an expression; throw an error here.
	}
	if (expType == Ast::BINARY) {
		Ast::Exp* watch = Ast::makeBinaryExp(
			pivot->opType, parseLeft(pivot, startId), parseRight(pivot, endId));
		return watch;
	}
	//parse unary expression
}

Ast::Exp* Parser::parseRight(Lexer::Token* token, int endId) {
	int startId = token->id;
	//we parse from startId to endId left to right
	//both tokens with startId and endId are excluded. 

	int min_precedence = 0;
	int base_precedence = 0;
	int expType = 0;

	if (endId - startId == 2) {
		//If there is only one token included,
		//we parse it as a primary expression.
		Ast::Exp* watch = parsePrimaryExpression(token->next);
		return watch;
	}

	Lexer::Token* pivot;

	while (token->next!= nullptr &&
		token->next->id != endId) {
		token = token->next;
		if (token->type == Lexer::OPERATOR) {
			if (OpType::isBinaryOp(token->opType) &&
				OpType::getPrecedence(token->opType) > min_precedence) {
				min_precedence = OpType::getPrecedence(token->opType);
				pivot = token;
				expType = Ast::BINARY;
			}
		}

	}
	if (expType == 0) {
		//Expected an expression; throw an error here.
	}
	if (expType == Ast::BINARY) {
		Ast::Exp* watch = Ast::makeBinaryExp(
			pivot->opType, parseLeft(pivot, startId), parseRight(pivot, endId));
		return watch;
	}
	//parse unary expression

}

Ast::Exp* Parser::parsePrimaryExpression(Lexer::Token* token) {
	if (token->type == Lexer::NUM_LITERAL) {
		//TODO: modify this so it actually return a decimal expression.
		//might need to modify makeDecimalExp too.

		for (char c : token->text) {
			if (c == '.') {
				return Ast::makeDecimalExp(3.13);
			}
		}

		std::stringstream ss(token->text);
		int num = 0;
		ss >> num;
		Ast::Exp* watch = Ast::makeIntegerExp(num);
		return watch;
	}
	else {
		return nullptr;
	}
	//TODO: need to expand
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
