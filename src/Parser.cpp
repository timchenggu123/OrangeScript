#include <iostream>
#include <sstream>
#include <vector>
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
		std::cerr << "error at parser scanner" << std::endl;
		exit(1);
	}

	//declare a parse stack
	std::vector<Ast::Exp*> parseStack;

	//initialize a new code block as rootNode
	list<Ast::Exp*>*args = new list<Ast::Exp*>;
	Ast::Exp* rootNode = Ast::makeCodeBlock(args);
	
	//initialize variables for scan
	Lexer::Token *token = tokens->front();
	int startId = 0;
	int endId = 0;
	int codeBlockType = Ast::getCodeBlockType(token); // we take a peek at the first token to determine the code block type.
	Ast::Exp* currentCodeBlock = rootNode;
	bool f_is_end = false;
	while (token != nullptr) 
	{
		endId = token->id;

		if (token->type == Lexer::BREAK ) {
			//we have reached the end of a statement
			//time to parse this statement
			if (startId + 1 == endId) {
				//if we have an empty line, 
				//we skip the line and do nothing
				token = token->next;
				continue;
			}
			if (codeBlockType == -999) {
				//-999 is the return value for the end keyword.
				//we pop off the stack.
				parseStack.back()->arguments->push_back(currentCodeBlock);
				currentCodeBlock = parseStack.back();
				parseStack.pop_back();
			}
			else if (codeBlockType != -1) {
				//we have found a keyword in the current statement
				//intializing a new code block.

				//we push the current codeblock on stack.
				parseStack.push_back(currentCodeBlock);

				if(codeBlockType == Ast::FOR)
				{
					args = new list<Ast::Exp*>;
					Ast::Exp* control = parseExpression(token, startId + 1, endId);
					Ast::Exp* forLoop = Ast::makeForLoop(control, args);
					currentCodeBlock = forLoop; 
				}
				else if(codeBlockType == Ast::WHILE)
				{
					args = new list<Ast::Exp*>;
					Ast::Exp* condition = parseExpression(token, startId + 1, endId);
					Ast::Exp* whileLoop = Ast::makeWhileLoop(condition, args); 
				}
				else if (codeBlockType == Ast::IF)
				{
					args = new list<Ast::Exp*>;
					Ast::Exp* condition = parseExpression(token, startId + 1, endId);
					Ast::Exp* ifConditional = Ast::makeIfConditional(condition, args); 
				}
				else{
					std::cerr << "Parser: Unexpected key word at beginning of statement at ln: " << token->ln;
					exit(1);
				}
			}
			else
			{
				//if no keyword found, add the statement to current codeblock
				currentCodeBlock->arguments->push_back(parseExpression(token, startId, endId));
			}

			startId = token->id;
			token = token->next;
			
			if (token != nullptr) {
				//right before we proceed to next statement, we
				//check the first token to determine if the token
				//initialzes a new level of code block i.e. a for
				//loop or a while loop, a function definition, etc. 

				codeBlockType = Ast::getCodeBlockType(token);
			}
			continue;
		}


	 	token = token->next;
	}
	if (!parseStack.empty()) {
		std::cerr << "Parser: Expecting end statement";
		exit(1);
	}
	ast->setRoot(rootNode);
}

Ast::Exp* Parser::parseExpression(Lexer::Token* token, int startId, int endId) {
	//parseExpression is basically parseLeft with modifications.

	int min_precedence = 0; 
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
		std::cerr << "Paser: Expected expression at ln:" << token->ln << " col: " << token->col;
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
				//rn this only returns a dummy expression
				return Ast::makeDecimalExp(3.13);
			}
		}

		std::stringstream ss(token->text);
		int num = 0;
		ss >> num;
		Ast::Exp* watch = Ast::makeIntegerExp(num);
		return watch;
	}
	else if (token->type == Lexer::VARIABLE) {
		return Ast::makeVariableExp(token->text);
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
