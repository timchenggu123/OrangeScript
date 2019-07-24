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


void Parser::scan(list<Lexer::Token> *tokens, Ast* ast)
{	
	if (tokens == nullptr) {
		//TODO throw error
		std::cerr << "error at parser schanner" << std::endl;
		exit(1);
	}
	list<Ast::Exp*> args;
	Ast::Exp* rootNode = Ast::makeCodeBlock(&args);
	
	Lexer::Token *token = &tokens->front();
	int startId = 0;
	int endId = 0;
	while (token->next != nullptr) 
	{
		if (token->opType == Lexer::BREAK) {
			if (startId == endId) {
				token = token->next;
				continue;
			}
			rootNode->arguments->push_back(parseExpression(token, startId, endId));
			token = token->next;
			startId = token->id;
			endId = token->id;
			continue;
		}
	 	token = token->next;
		endId = token->id;
	}
	ast->setRoot(rootNode);
}

Ast::Exp* Parser::parseExpression(Lexer::Token* token, int startId, int endId) {
	int min_precedence = INFINITY;
	int base_precedence = 0;
	int expType = 0;
	Lexer::Token* pivot;
	while (token->id != endId) {
		token = token->prev;
		if (token->type == Lexer::OPERATOR) {
			if (OpType::isBinaryOp(token->opType) &&
				OpType::getPrecedence(token->opType) < min_precedence) {
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
			return Ast::makeBinaryExp(
				pivot->type,parseLeft(pivot, startId), parseRight(pivot, endId));
	}
	//parse unary expression
	return nullptr;
}

Ast::Exp* Parser::parseLeft(Lexer::Token* token, int startId) {
	int min_precedence = INFINITY;
	int endId = token->id;
	int base_precedence = 0;
	int expType = 0;
	Lexer::Token* pivot;

	if (token->id - startId == 1) {
		return parsePrimaryExpression(token);
	}

	while (true) {
		token = token->prev;
		if (token->type == Lexer::OPERATOR) {
			if (OpType::isBinaryOp(token->opType) &&
				OpType::getPrecedence(token->opType) < min_precedence) {
				min_precedence = OpType::getPrecedence(token->opType);
				pivot = token;
				expType = Ast::BINARY;
			}
		}
		else {
			continue;
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
		if (token->type == Lexer::OPERATOR) {
			if (OpType::isBinaryOp(token->opType) &&
				OpType::getPrecedence(token->opType) < min_precedence) {
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
		return parseLeft(pivot, startId), parseRight(pivot, endId);
	}
	//parse unary expression

}

Ast::Exp* Parser::parsePrimaryExpression(Lexer::Token* token) {
	if (token->type == Lexer::NUM_LITERAL) {
		for (char c : token->text) {
			if (c == '.') {
				return Ast::makeDecimalExp(3.13);
			}
		}
	}
	else {
		std::stringstream ss(token->text);
		int num = 0;
		ss >> num;
		return Ast::makeIntegerExp(num);
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
