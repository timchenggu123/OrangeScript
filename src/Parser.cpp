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

	Lexer::Token* token_start = tokens->front();;
	Lexer::Token *token = token_start->next;
	int codeBlockType = Ast::getCodeBlockType(token); // we take a peek at the first token to determine the code block type.
	Ast::Exp* currentCodeBlock = rootNode;
	bool f_is_end = false;

	while (token != nullptr) 
	{

		if (token->type == Lexer::BREAK ) {
			//we have reached the end of a statement
			//time to parse this statement
			if (token_start->id + 1 == token->id) {
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
				//TODO: complete list of possible begin-statement keywords.
				if(codeBlockType == Ast::FOR)
				{
					args = new list<Ast::Exp*>;
					Ast::Exp* control = parseExpression(token_start->next, token);
					Ast::Exp* forLoop = Ast::makeForLoop(control, args);
					currentCodeBlock = forLoop; 
				}
				else if(codeBlockType == Ast::WHILE)
				{
					args = new list<Ast::Exp*>;
					Ast::Exp* condition = parseExpression(token_start->next, token);
					Ast::Exp* whileLoop = Ast::makeWhileLoop(condition, args); 
					currentCodeBlock = whileLoop;
				}
				else if (codeBlockType == Ast::IF)
				{
					args = new list<Ast::Exp*>;
					Ast::Exp* condition = parseExpression(token_start->next, token);
					Ast::Exp* ifConditional = Ast::makeIfConditional(condition, args); 
					currentCodeBlock = ifConditional;
				}
				else if (codeBlockType == Ast::DECLARE) {
					args = new list<Ast::Exp*>;
					Ast::Exp* assignment = parseExpression(token_start->next, token);
					Ast::Exp* declareVar = Ast::makeDeclareVar(assignment);
					currentCodeBlock = declareVar;
				}
				else{
					//This should theoretically never be called
					//If called, Ast defintion might be out of sync with lexer definition.
					std::cerr << "Parser: Unexpected key word at beginning of statement at ln: " << token->ln;
					exit(1);
				}
			}
			else
			{
				//if no keyword found, add the statement to current codeblock
				currentCodeBlock->arguments->push_back(parseExpression(token_start, token));
			}

			token_start = token;
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

Ast::Exp* Parser::parseExpression(Lexer::Token* token_start, Lexer::Token* token_end) {
	int startId = token_start->id;
	int endId = token_end->id;
	Lexer::Token* token = token_start;

	//parseExpression is basically parseLeft with modifications.
	int min_precedence = -1;
	int expType = -1;

	vector<Lexer::Token*> brkt_stk;

	Lexer::Token* pivot;
	
	//Check to see if the expression is enclosed by brackets. If so, skip
	if (token_start->next->text == "(" &&
		token_end->prev->text == ")") {
		return parseExpression(token_start->next, token_end->prev);
	}

	//Check to see if our expression length is 1. If so, return parse 
	//primary expression. 
	if (endId - startId == 2) {
		return parsePrimaryExpression(token_start->next);
	}

	while (token ->next != nullptr &&
		token->next->id != endId) {
		token = token->next;

		if (token->type == Lexer::OPERATOR &&
			brkt_stk.empty()) {

			if (OpType::isBinaryOp(token->opType) &&
				OpType::getPrecedence(token->opType) > min_precedence
				) 
			{
				min_precedence = OpType::getPrecedence(token->opType);
				pivot = token;
				expType = Ast::BINARY;
			}
			

		} else if(token->text == "(") {
			brkt_stk.push_back(token);

		}
		else if (token->text == ")") {

			if (brkt_stk.empty()) {
				std::cerr << "Parser:Unexpected closing bracket for token at ln:" << token->ln << " col:" << token->col;
				exit(1);
			}
			else {
				brkt_stk.pop_back();
			}

		}
		else {
			continue;
		}

	}
	if (expType == -1) {
		std::cerr << "Paser: Expected expression at ln:" << token->ln << " col: " << token->col;
	}
	if (!brkt_stk.empty()) {
		std::cerr << "Parser: Unmatched opening braket at ln:" << token->ln << " col:" << token->col;
	}

	if (expType == Ast::BINARY) {
			Ast::Exp* result = Ast::makeBinaryExp(
				pivot->opType,parseExpression(token_start, pivot), parseExpression(pivot,token_end));
			return result;
	}
	//parse unary expression

	//This should only be called if the Expression length is 0; 
	//Always keep this line checked. 
	return nullptr;
}


Ast::Exp* Parser::parsePrimaryExpression(Lexer::Token* token) {
	if (token->type == Lexer::NUM_LITERAL) {

		for (char c : token->text) {
			if (c == '.') {
				return Ast::makeDecimalExp(token->text);
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
	else if (token->type == Lexer::STR_LITERAL) {
		return Ast::makeStringExp(token->text);
	}
	else {
		return nullptr;
	}
	//TODO: need to expand
}


