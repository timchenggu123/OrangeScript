#include "Ast.h"




Exp * Ast::makeIntegerExp(int i)
{
	return nullptr;
}

Exp * Ast::makeStringExp(string s)
{
	return nullptr;
}

Exp * Ast::makeVariableExp(string s)
{
	return nullptr;
}

Exp * Ast::makeUnaryExp(int opType, Exp * left)
{
	return nullptr;
}

Exp * Ast::makeBinaryExp(int opType, Exp * left, Exp * right)
{
	return nullptr;
}

Exp * Ast::makeCallExp(string name, list<Exp>* arguments)
{
	return nullptr;
}

Ast::Ast()
{
}


Ast::~Ast()
{
}
