#include "Ast.h"

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

Ast::Exp * Ast::makeIntegerExp(int i)
{
	Exp *e = new Exp;
	e->expType = INTEGER;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = nullptr;
	e->right = nullptr;
	e->str_attr = "";
	e->int_attr = i;
	e->arguments = nullptr;
	return e;
}

Ast::Exp * Ast::makeStringExp(string s)
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
	return e;
}

Ast::Exp * Ast::makeVariableExp(string s)
{
	Exp *e = new Exp;
	e->expType = VARIABLE;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = nullptr;
	e->right = nullptr;
	e->str_attr = s;
	e->int_attr = NULL;
	e->arguments = nullptr;
	return e;
}

Ast::Exp * Ast::makeUnaryExp(int opType, Exp * l)
{
	Exp *e = new Exp;
	e->expType = UNARY;
	e->opType = opType;
	e->parent = nullptr;
	e->left = l;
	e->right = nullptr;
	e->str_attr = "";
	e->int_attr = NULL;
	e->arguments = nullptr;
	return e;
}

Ast::Exp * Ast::makeBinaryExp(int opType, Exp * l, Exp * r)
{
	Exp *e = new Exp;
	e->expType = BINARY;
	e->opType = opType;
	e->parent = nullptr;
	e->left = l;
	e->right = r;
	e->str_attr = "";
	e->int_attr = NULL;
	e->arguments = nullptr;
	return e;
}

Ast::Exp * Ast::makeCallExp(string name, list<Exp>* args)
{
	Exp *e = new Exp;
	e->expType = CALL;
	e->opType = NULL;
	e->parent = nullptr;
	e->left = nullptr;
	e->right = nullptr;
	e->str_attr = name;
	e->int_attr = NULL;
	e->arguments = args;
	return e;
}

int Ast::getExpType(Lexer::Token * token)
{
	//TODO implementation required. 
	return 0;
}

