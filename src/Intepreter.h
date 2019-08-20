#ifndef  INTEPRETER_H
#define INTEPRETER
#include "Parser.h"
#include "Ast.h"

class Intepreter
{
public:
	Intepreter();
	~Intepreter();
	void execute(Ast::Exp* root);
private:
	void post_order_walk(Ast::Exp* node);
	void intepret_node(Ast::Exp*node);
	void code_block_walk(Ast::Exp* node);
};


#endif 

