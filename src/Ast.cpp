#include "Ast.h"
#include <sstream>
Ast::Ast():
	root(nullptr)
{
}

Ast::~Ast()
{
}

Ast::Exp * Ast::getRoot()
{
	return root;
}

void Ast::setRoot(Exp * node)
{
	root = node;
}

Ast::Exp * Ast::makeIntegerExp(int i, int ln, int col)
{
	Exp *e = new Exp;
	e->expType = INTEGER;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = nullptr;
	e->right = nullptr;
	e->str_attr = "";
	e->deci_attr = NULL;
	e->int_attr = i;
	e->arguments = nullptr;
	e->is_int_attr = true;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp * Ast::makeDecimalExp(string s, int ln, int col)
{
	//TODO: add decimal attr

	std::stringstream ss(s);
	double num = 0;
	ss >> num;

	Exp *e = new Exp;
	e->expType = DECIMAL;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = nullptr;
	e->right = nullptr;
	e->str_attr = "";
	e->deci_attr = num;
	e->int_attr = NULL;
	e->arguments = nullptr;
	e->is_double_attr = true;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp * Ast::makeStringExp(string s, int ln, int col)
{
	Exp *e = new Exp;
	e->expType = STRING;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = nullptr;
	e->right = nullptr;
	e->str_attr = s;
	e->int_attr = NULL;
	e->arguments = nullptr;
	e->is_str_attr = true;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp * Ast::makeVariableExp(string s, int ln, int col)
{
	Exp *e = new Exp;
	e->expType = VARIABLE;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = nullptr;
	e->right = nullptr;
	e->str_attr = s;
	e->deci_attr = NULL;
	e->int_attr = NULL;
	e->arguments = nullptr;
	e->is_symbolic_return = true;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp * Ast::makeUnaryExp(int opType, Exp * l, int ln, int col)
{
	Exp *e = new Exp;
	e->expType = UNARY;
	e->opType = opType;
	e->parent = nullptr;
	e->left = l;
	e->right = nullptr;
	e->str_attr = "";
	e->int_attr = NULL;
	e->deci_attr = NULL;
	e->arguments = nullptr;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp * Ast::makeBinaryExp(int opType, Exp * l, Exp * r, int ln, int col)
{
	Exp *e = new Exp;
	e->expType = BINARY;
	e->opType = opType;
	e->parent = nullptr;
	e->left = l;
	e->right = r;
	e->str_attr = "";
	e->deci_attr = NULL;
	e->int_attr = NULL;
	e->arguments = nullptr;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp * Ast::makeCallExp(string name, list<Exp*>* args, int ln, int col)
{
	Exp *e = new Exp;
	e->expType = CALL;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = nullptr;
	e->right = nullptr;
	e->str_attr = name;
	e->deci_attr = NULL;
	e->int_attr = NULL;
	e->arguments = args;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp* Ast::makeCodeBlock(list<Exp*>* args, int ln, int col){
	Exp* e = new Exp;
	e->expType = CODE_BLK;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = nullptr;
	e->right = nullptr;
	e->str_attr = "";
	e->int_attr = NULL;
	e->deci_attr = NULL;
	e->arguments = args;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp* Ast::makeForLoop(Exp*control,list<Exp*>* args, int ln, int col){
	Exp* e = new Exp;
	e->expType = FOR;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = control;
	e->right = nullptr;
	e->str_attr = "";
	e->deci_attr = NULL;
	e->int_attr = NULL;
	e->arguments = args;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp* Ast::makeIfConditional(Exp*condition,list<Exp*>* args, int ln, int col){
	Exp* e = new Exp;
	e->expType = IF;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = condition;
	e->right = nullptr;
	e->str_attr = "";
	e->deci_attr = NULL;
	e->int_attr = NULL;
	e->arguments = args;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp* Ast::makeWhileLoop(Exp*condition,list<Exp*>* args, int ln, int col){
	Exp* e = new Exp;
	e->expType = WHILE;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = condition;
	e->right = nullptr;
	e->str_attr = "";
	e->deci_attr = NULL;
	e->int_attr = NULL;
	e->arguments = args;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp * Ast::makeDeclareVar(Exp * assignment, int ln, int col)
{
	Exp* e = new Exp;
	e->expType = WHILE;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = assignment;
	e->right = nullptr;
	e->str_attr = "";
	e->deci_attr = NULL;
	e->int_attr = NULL;
	e->arguments = nullptr;
	e->ln = ln;
	e->col = col;
	return e;
}

Ast::Exp * Ast::makeInstruction(int instruction, int ln, int col)
{
	Exp* e = new Exp;
	e->expType = INSTR;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = nullptr;
	e->right = nullptr;
	e->str_attr = "";
	e->deci_attr = NULL;
	e->int_attr = instruction;
	e->is_int_attr = true;
	e->arguments = nullptr;
	e->ln = ln;
	e->col = col;
	return e;
}

int Ast::getCodeBlockType(Lexer::Token* token)
{
	//Note, when adding a keyword, this method and isCodeBlock method
	//both need to be changed. 
	//TODO: complete this list
	
	//*Note while this looks similar to key_dict, not all keywords
	//initiate codeblocks. Thus, we need separate definition.

	if (token->type == Lexer::KEYWORD) {
		if (token->text == "for") {
			return FOR;
		}
		else if (token->text == "while") {
			return WHILE;
		}
		else if (token->text == "if") {
			return IF;
		}
		else if (token->text == "end") {
			return -999;
		}
		else if (token->text == "var") {
			return DECLARE;
		}
	}
	else {
		return -1;
	}
}

bool Ast::isCodeBlock(Exp * e)
{
	switch (e->expType) {
	case FOR:
	case WHILE:
	case IF:
	case DECLARE:
		return true;
	}

	return false;
}

void Ast::clearReturnVal(Exp * node)
{
	bool is_str_return = false;
	bool is_int_return = false;
	bool is_double_return = false;
	bool is_symbolic_return = false;

	bool is_str_attr = false;
	bool is_int_attr = false;
	bool is_double_attr = false;
}


