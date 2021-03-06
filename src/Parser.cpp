#include <iostream>
#include <sstream>
#include <vector>
#include "OpType.h"
#include "Parser.h"
#include "Lexer.h"
#include "Ast.h"
#include "Interpreter.h"


Parser::Parser()
{
}

Parser::~Parser()
{
}


void Parser::parse(list<Lexer::Token*> *tokens, Ast* ast, FunRegistry* fun_registry)
{	
	if (tokens == nullptr) {
		//TODO throw error
		std::cerr << "error at parser scanner" << std::endl;
		exit(1);
	}

	//declare a parse stack
	std::vector<Ast::Exp*> parseStack;

	//initialize a new code block as rootNode
	list<Ast::Exp*>*args = new list<Ast::Exp*>; //this is just temporary holder for args
	Ast::Exp* rootNode = Ast::makeCodeBlock(args,0,0);
	
	//initialize variables for scan

	Lexer::Token* token_start = tokens->front();;
	Lexer::Token *token = token_start->next;
	int codeBlockType = Ast::getCodeBlockType(token); // we take a peek at the first token to determine the code block type.
	Ast::Exp* currentCodeBlock = rootNode;
	bool f_is_end = false;
	bool is_function_body_block;

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
				if (is_function_body_block) {
					is_function_body_block = false;	
				}
				else {
					parseStack.back()->arguments->push_back(currentCodeBlock);
				}
				currentCodeBlock = parseStack.back();
				parseStack.pop_back();
			}
			else if (codeBlockType != -1) {
				//we have found a keyword in the current statement
				//intializing a new code block.
				
				//we save the current codeblock on stack.
				//then initialize a new one.
				parseStack.push_back(currentCodeBlock);

				//TODO: complete list of possible begin-statement keywords.
				if(codeBlockType == Ast::FOR)
				{
					args = new list<Ast::Exp*>;
					Ast::Exp* control = parseExpression(token_start->next, token);
					Ast::Exp* forLoop = Ast::makeForLoop(control, args,token->ln,token->col);
					currentCodeBlock = forLoop; 
				}
				else if(codeBlockType == Ast::WHILE)
				{
					args = new list<Ast::Exp*>;
					Ast::Exp* condition = parseExpression(token_start->next, token);
					Ast::Exp* whileLoop = Ast::makeWhileLoop(condition, args,token->ln, token->col);
					currentCodeBlock = whileLoop;
				}
				else if (codeBlockType == Ast::IF)
				{
					args = new list<Ast::Exp*>;
					Ast::Exp* condition = parseExpression(token_start->next, token);
					Ast::Exp* ifConditional = Ast::makeIfConditional(condition, args, token->ln, token->col);
					currentCodeBlock = ifConditional;
				}
				else if (codeBlockType == Ast::FUNCTION) {
					std::list<Ast::Exp*>* params = new list<Ast::Exp*>;
					std::string label = token_start->next->next->text;

					//fist, we parse a list of parameters
					//*Note, the lexer will automatically insert a _call operator here. Since we are not doing a call operation,
					//we can simply ignore that
					if (token_start->next->next->next->next->text == "(") { // next->next->next->next corresponds to keyword -> label -> _call operator-> left parenthesis
						Lexer::Token* temp_start = token_start->next->next->next->next;
						Lexer::Token* temp_end = token_start->next->next->next->next;
						while (true) {
							temp_end = temp_end->next;
							if (temp_end->type == Lexer::BREAK) {
								std::cerr << "Parser: Unexpected end at ln:" << temp_end->ln << " col:" << temp_end->col;
								exit(1);
							}
							else if (temp_end->text == ")") {
								params->push_back(parseExpression(temp_start, temp_end));
								break;
							}
							else if (temp_end->type == Lexer::DELIMITER) {
								params->push_back(parseExpression(temp_start, temp_end));
								temp_start = temp_end;
							}
						}

						//now, we make a codeBlock that is the acutal body of the function
						args = new list<Ast::Exp*>;
						Ast::Exp* body = Ast::makeCodeBlock(args, token_start->next->ln, token_start->next->col);
						Ast::Exp* functionBlock = Ast::makeFunction(label,params,body, token_start->next->ln, token_start->next->col);
						fun_registry->registerFunction(label, functionBlock);
						currentCodeBlock = body;
						is_function_body_block = true;
					}
					else {
						std::cerr << "Parser: Invalid syntax at ln:" << token_start->next->next->next->ln << "col:" << token_start->next->next->next->col;
						exit(1);
					}

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

	Lexer::Token* pivot = nullptr;

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

	//check to see if our expression starts with a keyword
	if (token_start->next->type == Lexer::KEYWORD) {
		std::string keyword = token_start->next->text;
		if (keyword == "print") {
			std::list<Ast::Exp*>* args = new std::list<Ast::Exp*>();
			args->push_back(parseExpression(token_start->next, token_end));
			return Ast::makeCallExp(Ast::makeVariableExp("_print", token->next->ln, token->next->col),
				args, token->next->ln, token->next->col
			);
		}
	}

	while (token->next != nullptr &&
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
			else if (OpType::isUnaryOp(token->opType) &&
				OpType::getPrecedence(token->opType) > min_precedence)
			{
				min_precedence = OpType::getPrecedence(token->opType);
				pivot = token;
				expType = Ast::UNARY;
			}


		}
		else if (token->text == "(") {
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
		Ast::Exp* result;
		if (pivot->opType == OpType::FUN_CALL) {
			 result = Ast::makeCallExp(
				parseExpression(token_start,pivot), parseDelimitedExpressions(pivot,token_end),
				pivot->ln, pivot->col);
		}
		else {
			result = Ast::makeBinaryExp(
				pivot->opType, parseExpression(token_start, pivot), parseExpression(pivot, token_end),
				pivot->ln, pivot->col);
		}

		return result;
	}

	if (expType == Ast::UNARY) {
		switch (OpType::LeftOrRightAssociate(pivot->opType)) {
			case OpType::RIGHT_ASSOC: {
				if (pivot->prev->id != startId) {
					std::cerr << "Parser: Unexpected expression at ln:" << pivot->ln << " col:" << pivot->col << std::endl;
					exit(1);
				}
				Ast::Exp* result = Ast::makeUnaryExp(
					pivot->opType, parseExpression(pivot, token_end),
					pivot->ln, pivot->col
				);
				return result;
			}
			case OpType::LEFT_ASSOC: {
				if (pivot->next->id != endId) {
					std::cerr << "Parser: Unexpected expression at ln:" << pivot->ln << " col:" << pivot->col << std::endl;
					exit(1);
				}
				Ast::Exp* result = Ast::makeUnaryExp(
					pivot->opType, parseExpression(token_start, pivot),
					pivot->ln, pivot->col
				);
				return result;
			}

			case OpType::INDETERMINATE:{
				Ast::Exp* result;
				if (pivot->prev->id == startId) {
					result = Ast::makeUnaryExp(
						pivot->opType, parseExpression(pivot, token_end),
						pivot->ln, pivot->col
					);
				}
				else if (pivot->next->id == endId) {
					result = Ast::makeUnaryExp(
						pivot->opType, parseExpression(token_start, pivot),
						pivot->ln, pivot->col
					);
				}
				else {
					std::cerr << "Parser: Unexpected expression at ln:" << pivot->ln << " col:" << pivot->col << std::endl;
					exit(1);
				}
				return result;
			}
		}
	}
	//parse unary expression

	//This should only be called if the Expression length is 0; 
	//Always keep this line checked. 
	return nullptr;
}

std::list<Ast::Exp*>* Parser::parseDelimitedExpressions(Lexer::Token * token_start, Lexer::Token * token_end)
{
	std::list<Ast::Exp*>* params = new list<Ast::Exp*>;
	Lexer::Token* temp_start = token_start;
	Lexer::Token* temp_end = token_start;
	while (true) {
		temp_end = temp_end->next;
		if (temp_end == token_end){
			params->push_back(parseExpression(temp_start, temp_end));
			break;
		}
		else if (temp_end->type == Lexer::DELIMITER) {
			params->push_back(parseExpression(temp_start, temp_end));
			temp_start = temp_end;
		}
	}
	return params;
}


Ast::Exp* Parser::parsePrimaryExpression(Lexer::Token* token) {
	if (token->type == Lexer::NUM_LITERAL) {

		for (char c : token->text) {
			if (c == '.') {
				return Ast::makeDecimalExp(token->text, token->ln, token->col);
			}
		}

		std::stringstream ss(token->text);
		int num = 0;
		ss >> num;
		Ast::Exp* watch = Ast::makeIntegerExp(num, token->ln, token->col);
		return watch;
	}
	else if (token->type == Lexer::VARIABLE) {
		return Ast::makeVariableExp(token->text,token->ln, token->col);
	}
	else if (token->type == Lexer::STR_LITERAL) {
		return Ast::makeStringExp(token->text, token->ln, token->col);
	}
	else if (token->type == Lexer::KEYWORD) {
		int instr = Interpreter::getInstructionType(token->text);
		if (instr == -999) {
			std::cerr << "Parser: Invalid instruction at ln:" << token->ln << " col" << token->col;
		}
		return Ast::makeInstruction(Interpreter::getInstructionType(token->text),
			token->ln, token->col);
	}
	else {
		return nullptr;
	}
	//TODO: need to expand
}


