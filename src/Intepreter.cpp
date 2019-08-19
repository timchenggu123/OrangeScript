#include "Intepreter.h"
#include "Ast.h"
Intepreter::Intepreter()
{
}

Intepreter::~Intepreter()
{
}

void Intepreter::execute(Ast::Exp * root)
{
	if (root->expType != Ast::CODE_BLK) {
		std::cerr << "parser: code block at root node";
		exit(0);
	}

	post_order_walk(root);
}

void Intepreter::post_order_walk(Ast::Exp * node)
{

}

void Intepreter::intepret(Ast::Exp * node)
{
}

