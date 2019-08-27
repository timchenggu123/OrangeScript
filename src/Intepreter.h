#ifndef  INTEPRETER_H
#define INTEPRETER
#include "Parser.h"
#include "Ast.h"

class Intepreter
{
public:
	Intepreter();
	~Intepreter();
	enum Instructions {
		NULL_INSTR,
		BREAK,
		CONTINUE
	};
	void execute(Ast::Exp* root);
	static int getInstructionType(std::string label);
private:
	int post_order_walk(Ast::Exp* node);
	void intepret_node(Ast::Exp*node);
	int code_block_walk(Ast::Exp* node);
	int iterate_args(Ast::Exp * node);
};


#endif 

